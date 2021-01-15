/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 23:42:50 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/15 21:14:49 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	arg_is_digit(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (!(ft_isdigit(arg[i])))
			return (0);
		i++;
	}
	return (1);
}

void		ft_exit(t_shell *shell)
{
	shell->exit = 1;
	ft_putstr_fd("exit", 2);
	if (shell->start->argc > 0)
	{
		if (arg_is_digit(shell->start->args[0]))
			shell->ret = ft_atoi(shell->start->args[0]);
		else
		{
			shell->ret = 255;
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(shell->start->args[0], 2);
			ft_putendl_fd(": numeric argument required", 2);
		}
	}
}
