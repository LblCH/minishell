/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 05:48:10 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/08 09:47:10 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env(t_shell *shell, char *env)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while(ft_isalnum(env[i]) || env[i] == '_')
	{
		len++;
		i++;
	}
	i = 0;
	while(shell->env[i])
	{
		if (!ft_strncmp(env, shell->env[i], len) \
			&& shell->env[i][len] == '=')
			return (&shell->env[i][len + 1]);
		i++;
	}
	return ("");
}