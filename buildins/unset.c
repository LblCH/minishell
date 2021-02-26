/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:49:23 by cdrennan          #+#    #+#             */
/*   Updated: 2021/02/26 20:58:53 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		**recreate_env_array(char **env, int delete)
{
	char **new;
	int i;
	int k;
	int count;

	count = env_count(env);
	new = malloc(sizeof(new) * count);
	i = 0;
	k = 0;
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
	new[i] = NULL;
	return (new);
}

int	ft_unset(t_shell *shell, char *arg)
{
	int i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			error_printing(arg, "unset: not a valid identifier: ");
			return(0);
		}
		i++;
	}
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], arg, ft_strlen(arg)) == 0)
		{
			shell->env = recreate_env_array(shell->env, i);
			return (0);
		}
		i++;
	}
	return (0);
}
