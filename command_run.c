/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:58:11 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/14 18:58:25 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_buildin(char *command)
{
	if (ft_strcmp(command, "echo") == 0 || ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0 || ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0 || ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}


void run_buildin (t_shell *shell)
{
	int ret;

	ret = 0;
	if (ft_strcmp(shell->start->command, "echo") == 0)
		ret = ft_echo(shell);
	if (ft_strcmp(shell->start->command, "cd") == 0)
		ret = ft_cd(shell);
	if (ft_strcmp(shell->start->command, "env") == 0)
		ret = ft_env(shell);
	if (ft_strcmp(shell->start->command, "export") == 0)
		ret = ft_export(shell);
	if (ft_strcmp(shell->start->command, "unset") == 0)
		ret = ft_unset(shell);
	if (ft_strcmp(shell->start->command, "pwd") == 0)
		ret = ft_pwd();

}

void run_execve(t_shell *shell)
{
	int i;

	i = 0;
	printf ("I'm execve command: %s\n", shell->start->command);
	while (ft_strncmp(shell->env[i], "PATH=", 5) != 0)
		i++;

}

void cmd_run (t_shell *shell)
{

	if (!ft_strcmp(shell->start->command, "exit"))
		ft_exit(shell);
	else if(is_buildin(shell->start->command))
		run_buildin(shell);
	else
		run_execve(shell);
}