/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 05:48:10 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/08 05:55:23 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env(t_shell *shell, char *env)
{
	int i;

	i = 0;
	while(shell->env[i])
	{
		if (!ft_strncmp(env, shell->env[i], ft_strlen(env)) \
			&& shell->env[i][ft_strlen(env)] == '=')
			return (&shell->env[i][ft_strlen(env) + 1]);
		i++;
	}
	return (NULL);
}