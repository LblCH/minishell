/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:49:15 by cdrennan          #+#    #+#             */
/*   Updated: 2021/02/27 18:17:42 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (ft_isdigit(env[i]) == 1 || env[i] == '=')
		return (-1);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0 && env[i] != '_')
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (1);
	return (2);
}

char		**create_env_array(char **env, char *to_add, int var)
{
	char	**new;
	int		i;
	int		count;

	count = env_count(env);
	i = (var == 1) ? 2 : 1;
	new = malloc(sizeof(new) * (count + i));
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = (var == 1) ? ft_strdup(to_add) : NULL;
	if (var == 1)
	{
		new[i] = ft_strdup(to_add);
		new[i + 1] = NULL;
	}
	else
		new[i] = NULL;
	return (new);
}

int			ft_export(t_shell *shell)
{
	int count;
	int ret;
	int i;

	if (!shell->start->args[1])
	{
		count = env_count(shell->env);
		sort_env(shell->env, count);
		env_print(shell->env);
		return (0);
	}
	else
	{
		i = 1;
		while (shell->start->args[i])
		{
			ret = env_validation(shell->start->args[i]);
			if (ret < 0)
				error(shell->start->args[i], "export: not valid identifier: ");
			if (ret == 2)
				add_env(shell, shell->start->args[i]);
			i++;
		}
	}
	return (ret < 0 ? 1 : 0);
}
