/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:49:23 by cdrennan          #+#    #+#             */
/*   Updated: 2021/03/06 05:48:21 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**recreate_env_array(char **env, int delete, int i, int k)
{
	char	**new;
	int		count;

	count = env_count(env);
	new = malloc(sizeof(new) * count);
	while (k < (count - 1))
	{
		if (k == delete)
		{
			new[i] = ft_strdup(env[k + 1]);
			i++;
			k += 2;
		}
		else
			new[i++] = ft_strdup(env[k++]);
	}
	if (k == (count - 1) && k != delete)
	{
		new[i] = ft_strdup(env[k]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int			check_arg(char *arg)
{
	int i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			error(arg, "unset: not a valid identifier: ");
			return (0);
		}
		i++;
	}
	return (1);
}

int			ft_unset(t_shell *shell, char *arg)
{
	int			i;
	char		**tmp;

	if (!check_arg(arg))
		return (0);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], arg, ft_strlen(arg)) == 0)
		{
			tmp = shell->env;
			shell->env = recreate_env_array(tmp, i, 0, 0);
			free_tab(tmp);
			return (0);
		}
		i++;
	}
	return (0);
}
