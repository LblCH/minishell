/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:58:11 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/16 19:10:22 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		run_buildin(t_shell *shell, char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		shell->ret = ft_echo(shell->start->argc, shell->start->args);
	else if (ft_strcmp(cmd, "cd") == 0)
		shell->ret = ft_cd(shell);
	else if (ft_strcmp(cmd, "env") == 0)
		shell->ret = ft_env(shell->env);
	else if (ft_strcmp(cmd, "export") == 0)
		shell->ret = ft_export(shell);
	else if (ft_strcmp(cmd, "unset") == 0)
		shell->ret = ft_unset(shell, shell->start->args[0]);
	else if (ft_strcmp(cmd, "pwd") == 0)
		shell->ret = ft_pwd();
}

char		*check_location(char **paths, char *cmd)
{
	char *valid_path;
	DIR *dir;
	struct dirent *dir_content;
	int i;

	i = 0;
	while (paths[i++])
	{
		if(!(dir = opendir(paths[i])))
			return (NULL);
		dir_content = readdir(dir);
		while (dir_content)
		{
			if (ft_strcmp(dir_content->d_name, cmd) == 0)
			{
				valid_path = ft_strjoin_with_slash(paths[i], cmd);
				closedir(dir);
				return (valid_path);
			}
			dir_content = readdir(dir);
		}
	}
	closedir(dir);
	return (0);
}

int 		run_execve(t_shell *shell, char *path)
{
	pid_t pid;
	int ret;

	pid = fork();
	if (pid == 0)
	{
		execve(path, shell->start->args, shell->env_export);
		exit (pid);
	}
	else
		waitpid(pid, &ret, 0);
	return (0);
}

void		prep_execve(t_shell *shell)
{
	int i;
	char **paths;
	char* valid_path;

	i = 0;

	while (shell->env && ft_strncmp(shell->env[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(shell->env[i], ':');
	paths[0] = paths[0] + 5;
	valid_path = check_location(paths, shell->start->command);
	run_execve (shell, valid_path);
}

void		cmd_run(t_shell *shell)
{
	if (!ft_strcmp(shell->start->command, "exit"))
		ft_exit(shell);
	else if (is_buildin(shell->start->command))
		run_buildin(shell, shell->start->command);
	else
		prep_execve(shell);
}
