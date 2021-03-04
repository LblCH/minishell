/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:03:00 by cdrennan          #+#    #+#             */
/*   Updated: 2021/02/28 00:33:37 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		status_return(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			ft_putstr_fd("\n", 2);
			return (130);
		}
		if (WTERMSIG(status) == 3)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			return (131);
		}
		if (WTERMSIG(status) == 15)
			return (143);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}

void	catch_sig(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("👻 \033[35mGhost'm IN i-Shell ⇥ \033[0m", 1);
		g_sig.catched = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
}

void	init(t_shell *shell)
{
	shell->err = 0;
	g_sig.pid = -10;
	g_sig.catched = 0;
}
