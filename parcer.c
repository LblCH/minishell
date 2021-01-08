/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 04:15:50 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/08 07:19:00 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		quotes_cl(char *line)
{
	int open;
	int open2;

	open = 0;
	open2 = 0;
	while(*line)
	{
		if (*line == '\'' && open == 0)
			open = 1;
		else if (*line == '\"' && open2 == 0)
			open2 = 1;
		else if (*line == '\'' && open == 1)
			open = 0;
		else if (*line == '\"' && open2 == 1)
			open2 = 0;
		line++;
	}
	return (open || open2);
}

int		ft_parcer(t_shell *shell)
{
	while (ft_isspace(*shell->command))
		shell->command++;
	if(ft_strchr(shell->command, '\'') || ft_strchr(shell->command, '\"'))
	{
		if(quotes_cl(shell->command))
		{
			ft_putstr_fd("Non couple quotes.\n", 2);
			return (0);
		}
		shell->command++;
	}
	if(!ft_strncmp("exit", shell->command, 4))
		return (1);
	return (0);
}