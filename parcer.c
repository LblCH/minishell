/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 04:15:50 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/20 23:55:14 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*redirect(t_shell *shell, char *line)
{
	char *file;
	int d_red;
	char redir;

	redir = *line++;
	(shell->fd >= 0) ? close(shell->fd) : (0);
	file = ft_strdup("");
	d_red = (*line == '>') ? 1 : 0;
	(*line == '>') ? line++ : (0);
	while (ft_isspace(*line))
		line++;
	while (ft_isalnum(*line))
		file = add_char(file, *line++);
	shell->fd_type = 1;
	if (redir == '<')
	{
		shell->fd_type = -1;
		if ((shell->fd = open(file, O_RDWR)) < 0 )
			return (NULL);
	}
	else if (d_red == 0)
		shell->fd = open(file, O_RDWR | O_CREAT, 0644);
	else
		shell->fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(file);
	return (line);
}

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
	else if (*line == '<' || *line == '>')
		line = redirect(shell, line);
	return (line);
}

char		*separators(t_shell *shell, char *line)
{
	int pipe_fd[2];

	if (*line == '|')
		pipe(pipe_fd);
	if (*line == '|' && token_last(shell->start)->fd_out < 0)
	{
		token_last(shell->start)->is_piped = 1;
		token_last(shell->start)->fd_out = pipe_fd[1];
	}
	token_last(shell->start)->next = new_token();
	if (*line == '|')
		token_last(shell->start)->fd_in = pipe_fd[0];
	line++;
	add_token(shell, token_last(shell->start), line);
	return(shell->line_left);
}

char		*ft_parcer(t_shell *shell, char *line)
{
	char *res;

	res = ft_strdup("");
	while (ft_isspace(*line))
		line++;
	while (*line && *line != ' ')
	{
		if (ft_strchr("\'\"$\\><", *line))
			line = spec_simbol(shell, line, &res);
		else if (*line == ';' || *line == '|')
			line = separators(shell, line);
		else
		{
			res = add_char(res, *line);
			line++;
		}
	}
	shell->line_left = line;
	return (res);
}