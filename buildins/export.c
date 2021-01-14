/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:49:15 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/14 21:33:48 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env_print (char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

int		env_validation(const char *env)
{
	int		i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (-1);
	if ((env[0]) == '=')
		return (-1);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (1);
	return (2);
}

void error_printing (char *env)
{
	ft_putstr_fd("export: not a valid identifier: ", 2);
	ft_putendl_fd(env, 2);
}


int add_env (t_shell *shell)
{
	int i;
	char *name;

	i = 0;
	name = ft_calloc(1, ft_strlen(shell->start->args[0]));
	name = env_name(shell->start->args[0], name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0)
		{
			shell->env[i] = ft_strdup(shell->start->args[0]);
			shell->env_export[i] = ft_strdup(shell->start->args[0]);
			return (0);
		}
		i++;
	}
	free(name);
	shell->env[i] = ft_strdup(shell->start->args[0]);
	shell->env_export[i] = ft_strdup(shell->start->args[0]);
	return (0);
}

int ft_export (t_shell *shell)
{
	int count;
	int ret;

	if (shell->start->argc < 1)
	{
		count = env_count(shell->env);
		sort_env(shell->env_export, count);
		env_print(shell->env_export);
		return (0);
	}
	else
	{
		ret = env_validation(shell->start->args[0]);
		if (ret < 0)
		{
			error_printing(shell->start->args[0]);
			return (1);
		}
		if (ret == 2)
			add_env(shell);
	}
	return (0);
}
