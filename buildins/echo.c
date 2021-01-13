/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:23:11 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/12 10:54:45 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int argc_count (char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
int ft_echo (char **args)
{
	int n_option;
	int i;
	int argc;

	n_option = 0;
	i = 0;
	argc = argc_count(args);
	if (argc > 1)
	{
		if (ft_strcmp(args[0], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (args[++i] != NULL)
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				ft_putchar_fd(' ', 1);
		}
	}
	if (n_option == 0)
		write (1, "\n", 1);
	return (0);
}
