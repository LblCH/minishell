/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:23:11 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/15 21:07:50 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_shell *shell)
{
	int n_option;
	int i;

	n_option = 0;
	i = 0;
	if (shell->start->argc > 0)
	{
		if (ft_strcmp(shell->start->args[0], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (shell->start->argc > 0)
		{
			ft_putstr_fd(shell->start->args[i], 1);
			if (shell->start->args[i + 1] && shell->start->args[i][0] != '\0')
				ft_putchar_fd(' ', 1);
			shell->start->argc -= 1;
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}
