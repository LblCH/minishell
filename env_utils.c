/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:00:01 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/14 21:08:32 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int env_count (char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char *env_name(const char *src, char *dest)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '=';
	dest[i + 1] = '\0';
	return (dest);
}