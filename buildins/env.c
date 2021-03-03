/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:55:55 by cdrennan          #+#    #+#             */
/*   Updated: 2021/02/27 18:35:19 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **env, t_token *token)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], (token->fd_out > 0) ? token->fd_out : 1);
		i++;
	}
	close(token->fd_out);
	return (0);
}
