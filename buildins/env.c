/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:55:55 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/27 13:51:47 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}
