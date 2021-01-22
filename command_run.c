/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:58:11 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/22 21:37:54 by cdrennan         ###   ########.fr       */
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
	pid_t pid;
	int ret;


	ret = 0;
	pid = fork();

	if (pid == 0)
	{
		execve(path, shell->start->args, shell->env_export);
		ret = error_execve(path);
		exit(ret);
	}
	else
		waitpid(pid, &ret, 0);
	return (ret);
}

int		prep_execve(t_shell *shell)
{
	int i;
	char **paths;
	char *valid_path;
	int ret;

	i = 0;
	while (shell->env && ft_strncmp(shell->env[i], "PATH=", 5) != 0)
		i++;
	if (shell->env[i] == NULL)
		return (run_execve(shell, shell->start->args[0]));
	paths = ft_split(shell->env[i] + 5, ':');
	valid_path = check_location(paths, shell->start->command);
	if (valid_path)
		ret = run_execve(shell, valid_path);
	else
		ret = run_execve(shell, shell->start->args[0]);
	return (ret);
}


void		cmd_run(t_shell *shell)
{
	if (!ft_strcmp(shell->start->command, "exit"))
		ft_exit(shell);
	else if (is_buildin(shell->start->command))
		shell->ret = run_buildin(shell, shell->start->command);
	else
		shell->ret = prep_execve(shell);
}
