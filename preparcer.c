/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 11:34:36 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/26 11:45:11 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_redirect(char *line, int i)
{
	char *token;

	token = add_char("", line[i]);
	i++;
	if (line[i - 1] == '>' && line[i] == '>')
		token = add_char(token, line[i++]);
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
	{
		ft_putstr_fd("mini: syntax error near unexpected token `newline'\n", 2);
		free(token);
		return (1);
	}
	free(token);
	return (0);
}

int		check_semicolon(char *line, int i)
{
	char *token;

	i++;
	token = ft_strdup(";;");
	while (ft_isspace(line[i]))
	{
		i++;
		token = ft_strdup(";");
	}
	if (line[i] == ';')
	{
		ft_putstr_fd("mini: syntax error near unexpected token `", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'\n", 2);
		free(token);
		return (1);
	}
	free(token);
	return (0);
}

int		preparcer(char *line)
{
	int i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == ';' && check_semicolon(line, i))
			return (1);
		else if (ft_strchr("><", line[i]) && check_redirect(line, i))
			return (1);
		else if (line[i + 1] && line [i] == '|' && line [i + 1] == '|')
		{
			ft_putstr_fd("mini: syntax error near unexpected token `||'\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
