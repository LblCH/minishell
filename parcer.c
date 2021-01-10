/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 04:15:50 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/10 13:45:30 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*spec_simbol(t_shell *shell, char *line, char **res)
{
	if(*line == '$')
	{
		*res = ft_strjoin(*res, get_env(shell, ++line));
		while (ft_isalnum(*line) || *line == '_')
			line++;
	}
	else if(*line == '\'' || *line == '\"')
		line = quotes_handler(shell, line, res, *line);
	return (line);
}

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

char		*ft_parcer(t_shell *shell, char *line)
{
	char s[2];
	char *res;

	s[1] = '\0';
	while(ft_isspace(*line))
		line++;
	while(*line && *line != ' ')
	{
		if(ft_strchr("\'\"$", *line))
			line = spec_simbol(shell, line, &res);
		else
		{
			s[0] = *line;
			res = ft_strjoin(shell->command, s);
			line++;
		}
	}
	return (res);
}