/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:58:11 by cdrennan          #+#    #+#             */
/*   Updated: 2021/02/26 11:36:37 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_buildin(t_shell *shell, char *cmd)
{
	int ret;
	int i;

	ret = 0;
	i = 1;
	if (ft_strcmp(cmd, "echo") == 0)
		ret = ft_echo(shell->start);
	else if (ft_strcmp(cmd, "cd") == 0)
		ret = (ft_cd(shell));
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(shell->env);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(shell);
	else if (ft_strcmp(cmd, "unset") == 0)
	{
		while (shell->start->args[i])
		{
			ft_unset(shell, shell->start->args[i]);
			i++;
		}
	}
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

int		child_process(t_shell *shell, t_token *token)
{
	int ret;
//	printf("--------------\nToken added\n");
//	printf("fd_in: %d fd_out: %d fd_out_prev: %d\n", token->fd_in, token->fd_out, token->fd_out_prev);
//	int i = 0;
//	while (token->args && token->args[i])
//	{
//		printf("arg %d: %s\n", i, token->args[i]);
//		i++;
//	}
//	printf("--------------\n");
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
	ret = cmd_run(shell, token);
	return (ret);
}

int 		start_execve(t_shell *shell)
{
	int ret;
	int n;
	pid_t pid;
	struct s_token *token;

	token = shell->start;
	n = 0;
	while (token)
	{
		ret = 0;
		n++;
		if (token->args && (!ft_strcmp(token->args[0], "exit")))
		{
			ft_exit(shell);
			return (shell->ret);
		}
		else if (token->args && (is_buildin(token->args[0])))
			ret = run_buildin(shell, token->args[0]);
		else
		{
			pid = fork();
			if (pid == 0)
				ret = child_process(shell, token);
		}
		token = token->next;
	}
	while(n--)
		wait(&ret);
	clear_tokens(shell);
	ret = WEXITSTATUS(ret);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.ret);
	return (ret);
}

void		prep_execve(t_shell *shell, t_token *token)
{
	int i;
	char **paths;
	char *valid_path;

	i = 0;
	while (shell->env && shell->env[i] && ft_strncmp(shell->env[i], \
															"PATH=", 5) != 0)
		i++;
	if (shell->env[i] == NULL)
		(ft_strchr(token->args[0], '/') != NULL) ? \
					execve(token->args[0], token->args, shell->env) : 0;
	paths = ft_split(shell->env[i] + 5, ':');
	valid_path = check_location(paths, token->args[0]);
	free_tab(paths);
	if (valid_path)
		(ft_strchr(valid_path, '/') != NULL) ? execve(valid_path, token->args, \
															shell->env) : 0;
	else
		(ft_strchr(token->args[0], '/') != NULL) ? \
					execve(token->args[0], token->args, shell->env) : 0;
	free(valid_path);
}


int		cmd_run(t_shell *shell, t_token *token)
{
	char *cmd;
	int ret;

	if(token->args)
		cmd = token->args[0];
	else
		cmd = NULL;
	if (cmd)
		prep_execve(shell, token);
	ret = error_execve(token->args[0]);
	clear_tokens(shell);
	exit(ret);
}
