/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:49:15 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/12 19:44:35 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int env_count (char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char **sort_env (char **env, int y)
{
	int x;
	char *tmp;
	int sorted;

	sorted = 0;
	while (env && sorted == 0)
	{
		sorted = 1;
		x = 0;
		while (x < y - 1)
		{
			if (ft_strcmp(env[x], env[x + 1]) > 0)
			{
				tmp = env[x];
				env[x] = env[x + 1];
				env [x + 1] = tmp;
				sorted = 0;
			}
			x++;
		}
		y--;
	}
	return (env);
}

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

int ft_export (t_shell *shell)
{
	char **tab;
	int count;

	if (shell->start->argc < 1)
	{
		count = env_count(shell->env);
		tab = shell->env;
		sort_env(tab, count);
		env_print(tab);
	}
	return (0);
}
