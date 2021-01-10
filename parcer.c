/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 04:15:50 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/08 09:58:08 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*spec_simbol(t_shell *shell, char *line)
{
	if(*line == '$')
	{
		printf("%s\n", line);
		shell->command = ft_strjoin(shell->command, get_env(shell, line + 1));
		while (ft_isalnum(*line) || *line == '_')
		{
//			printf("%s\n", line);
			line++;
		}
	}
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

int		ft_parcer(t_shell *shell, char *line)
{
	char s[2];
	int i;

	s[1] = '\0';
	i = 0;
	while(ft_isspace(*line))
		line++;
	while(*line)
	{
		if(ft_strchr("\'\"$", *line))
			line = spec_simbol(shell, line);
		s[0] = *line;
		shell->command = ft_strjoin(shell->command, s);
		line++;
	}
//	if(ft_strchr(line, '\'') || ft_strchr(line, '\"'))
//	{
//		if(quotes_cl(line))
//		{
//			ft_putstr_fd("Non couple quotes.\n", 2);
//			return (0);
//		}
//		shell->command++;
//	}
	printf("%s\n", shell->command);
	if(!ft_strncmp("exit", shell->command, 4))
		return (1);
	return (0);
}