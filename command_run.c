/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:58:11 by cdrennan          #+#    #+#             */
/*   Updated: 2021/02/24 18:40:26 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_buildin(t_shell *shell, char *cmd)
{
	int ret;

	ret = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		ret = ft_echo(shell->start);
	else if (ft_strcmp(cmd, "cd") == 0)
		ret = (ft_cd(shell));
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(shell->env);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(shell);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(shell, shell->start->args[1]);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ret = (ft_pwd());
	return (ret);
}

int			error_execve(char *path)
{
	DIR *dir;
	int fd;
	int ret;

	fd = open(path, O_WRONLY);
	dir = opendir(path);
	ft_putstr_fd("👻 \033[35mGhost'm IN i-Shell: \033[0m", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && dir == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && dir != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && dir == NULL)
		ft_putendl_fd(": Permission denied", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && dir == NULL))
		ret = 127;
	else
		ret = 126;
	if (dir)
		closedir(dir);
	if (fd > 0)
		close(fd);
	return (ret);
}

int 		run_execve(t_shell *shell, char *path)
{
	int ret;
	int n;
	struct s_token *token;

	token = shell->start;
	n = 0;
	while (token)
	{
		ret = 0;
		n++;
		g_sig.pid = fork();
		if (g_sig.pid == 0)
		{
			if (token->fd_in != -1)
			{
				dup2(token->fd_in, 0);
				(token->fd_out_prev != -1) ? close(token->fd_out_prev) : 0;
			}
			if (token->fd_out != -1)
			{
				dup2(token->fd_out, 1);
				if (token->next)
					(token->next->fd_in != -1) ? close(token->next->fd_in) : 0;
			}
			if (ft_strchr(path, '/') != NULL)
				execve(path, token->args, shell->env);
			ret = error_execve(path);
			clear_tokens(shell);
			exit(ret);
		}
		token = token->next;
	}
	while(n--)
		wait(&ret);
	ret = WEXITSTATUS(ret);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.ret);
	return (ret);
}

int		prep_execve(t_shell *shell)
{
	int i;
	char **paths;
	char *valid_path;
	int ret;

	i = 0;
	while (shell->env && shell->env[i] && ft_strncmp(shell->env[i], "PATH=", 5) != 0)
		i++;
	if (shell->env[i] == NULL)
		return (run_execve(shell, shell->start->args[0]));
	paths = ft_split(shell->env[i] + 5, ':');
	valid_path = check_location(paths, shell->start->args[0]);
	if (valid_path)
		ret = run_execve(shell, valid_path);
	else
		ret = run_execve(shell, shell->start->args[0]);
	return (ret);
}


void		cmd_run(t_shell *shell)
{
	char *cmd;

	if(shell->start->args)
		cmd = shell->start->args[0];
	else
		cmd = NULL;
	if (cmd && (!ft_strcmp(cmd, "exit")))
		ft_exit(shell);
	else if (cmd && (is_buildin(cmd)))
		shell->ret = run_buildin(shell, cmd);
	else if (cmd)
		shell->ret = prep_execve(shell);
	clear_tokens(shell);
}
