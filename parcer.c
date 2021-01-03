/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 04:15:50 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/03 07:26:37 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quotes_cl(char *line)
{
	int open;

	open = 0;
	while(line)
	{
		if (*line == '\'' && open == 0)
			open = 1;
		else if (*line == '\"' && open == 0)
			open = 2;
		else if (*line == '\'' && open == 1)
			open = 0;
		else if (*line == '\"' && open == 2)
			open = 0;
		line++;
	}
	return (open);
}

int ft_parcer(t_shell *shell)
{
	char *line;

	if(get_next_line(0, &line) < 0)
		ft_putstr_fd("Failed GNL", 2);
	while(ft_isspace(*line))
		line++;
	while(*line != '\0')
	{
		if((ft_strchr(line, '\'') || ft_strchr(line, '\"')) && quotes_cl(line))
		{
			ft_putstr_fd("Non couple quotes.", 2);
			return(0);
		}

	}
	return (0);
}