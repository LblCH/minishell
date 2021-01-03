/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 04:15:50 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/03 06:57:55 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_parcer(t_shell *shell)
{
	char *line;

	ft_putstr_fd("💀 \033[36mMiNishell ⇥ \033[0m", 1);
	if(get_next_line(0, &line) < 0)
		ft_putstr_fd("Failed GNL", 2);
	while(ft_isspace(*line))
		line++;
	while(*line != '\0')
	{
		if(ft_strchr(line, '\'\"')
	}
	return (0);
}