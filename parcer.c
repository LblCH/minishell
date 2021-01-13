/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 04:15:50 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/13 23:09:14 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*spec_simbol(t_shell *shell, char *line, char **res)
{
	if (*line == '$')
	{
		*res = ft_strjoin(*res, get_env(shell, ++line));
		while (ft_isalnum(*line) || *line == '_')
			line++;
	}
	else if (*line == '\\')
		line = escape_handler(++line, res);
	else if (*line == '\'' || *line == '\"')
		line = quotes_handler(shell, line, res, *line);
	return (line);
}

void 		add_token(t_shell *shell, t_token *token, char *line)
{
	int i;

	i = 0;
	token->command = ft_parcer(shell, line);
	printf("command: %s\n", token->command);
	while(*shell->line_left)
	{
		token->args = realloc_args(token, i + 1);
		token->args[i] = ft_strjoin("", \
											ft_parcer(shell, shell->line_left));
		printf("arg %d: %s\n", i, token->args[i]);
		i++;
	}
}

char		*ft_parcer(t_shell *shell, char *line)
{
	char s[2];
	char *res;

	s[1] = '\0';
	res = ft_strdup("");
	while (ft_isspace(*line))
		line++;
	if (!(*line))
		return (res);
	while (*line && *line != ' ')
	{
		if (ft_strchr("\'\"$\\", *line))
			line = spec_simbol(shell, line, &res);
		else if (*line == ';')
		{
			line++;
//			printf("left: %s\n", line);
			token_last(shell->start)->next = new_token();
			add_token(shell, token_last(shell->start), line);
			line = shell->line_left;
		}
		else
		{
			s[0] = *line;
			res = ft_strjoin(res, s);
			line++;
		}
	}
	shell->line_left = line;
	return (res);
}