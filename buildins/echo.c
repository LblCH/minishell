/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:23:11 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/15 21:17:20 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(int argc, char **argv)
{
	int n_option;
	int i;

	n_option = 0;
	i = 0;
	if (argc > 0)
	{
		if (ft_strcmp(argv[0], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (argc > 0)
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && argv[i][0] != '\0')
				ft_putchar_fd(' ', 1);
			argc -= 1;
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}
