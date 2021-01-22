/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:49:15 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/22 19:41:33 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		env_print(char **env)
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

int			env_validation(const char *env)
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

int			ft_export(t_shell *shell)
{
	int count;
	int ret;

	if (!shell->start->args[1])
	{
		count = env_count(shell->env);
		sort_env(shell->env_export, count);
		env_print(shell->env_export);
		return (0);
	}
	else
	{
		ret = env_validation(shell->start->args[1]);
		if (ret < 0)
		{
			error_printing(shell->start->args[1],
				  "export: not a valid identifier: ");
			return (1);
		}
		if (ret == 2)
			add_env(shell, shell->start->args[1]);
	}
	return (0);
}
