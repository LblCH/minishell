/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:23:11 by cdrennan          #+#    #+#             */
/*   Updated: 2021/02/27 18:35:19 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_token *token)
{
	int n_option;
	int i;

	n_option = 0;
	i = 1;
	if (token->args[1])
	{
		if (ft_strcmp(token->args[1], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (token->args[i])
		{
			ft_putstr_fd(token->args[i],
				(token->fd_out > 0) ? token->fd_out : 1);
			if (token->args[i + 1] && token->args[i][0] != '\0')
				ft_putchar_fd(' ', (token->fd_out > 0) ? token->fd_out : 1);
			i++;
		}
	}
	if (n_option == 0)
		write((token->fd_out > 0) ? token->fd_out : 1, "\n", 1);
	return (0);
}
