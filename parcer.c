/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 04:15:50 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/06 01:52:35 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*redirect(t_shell *shell, char *line, char *file)
{
	int		d_red;
	char	redir;

	redir = *line++;
	(shell->fd >= 0) ? close(shell->fd) : 0;
	d_red = (*line == '>') ? 1 : 0;
	(*line == '>') ? line++ : (0);
	while (ft_isspace(*line))
		line++;
	while (*line && (ft_isalnum(*line) || ft_strchr("._-", *line)))
		file = add_char(file, *line++);
	shell->fd_type = 1;
	if (redir == '<')
	{
		shell->fd_type = -1;
		if ((shell->fd = open(file, O_RDWR)) < 0)
			return (file_error(shell, file));
	}
	else if (d_red == 0)
		shell->fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		shell->fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_free(file);
	return (line);
}

char		*spec_simbol(t_shell *shell, char *line, char **res)
{
	if (*line == '$')
	{
		if (!ft_isalnum(*(line + 1)) && !ft_strchr("\'\"?", *(line + 1)))
		{
			*res = add_char(*res, '$');
			line++;
		}
		else
			line = variable_add(shell, line);
	}
	else if (*line == '\\')
		line = escape_handler(++line, res);
	else if (*line == '\'' || *line == '\"')
		line = quotes_handler(shell, line, res, *line);
	return (line);
}

char		*separators(t_shell *shell, char *line)
{
	int pipe_fd[2];

	if (*line == '|')
	{
		pipe(pipe_fd);
		if (token_last(shell->start)->fd_out < 0)
			token_last(shell->start)->fd_out = pipe_fd[1];
		token_last(shell->start)->next = new_token();
		if (*line == '|')
		{
			token_last(shell->start)->fd_in = pipe_fd[0];
			token_last(shell->start)->fd_out_prev = pipe_fd[1];
		}
		line++;
		add_token(shell, token_last(shell->start), line);
	}
	return (shell->line_left);
}

char		*ft_parcer(t_shell *shell, char *line)
{
	char *res;

	res = ft_strdup("");
	while (ft_isspace(*line))
		line++;
	while (line && *line && *line != ' ')
	{
		if (ft_strchr("\'\"$\\", *line))
			line = spec_simbol(shell, line, &res);
		else if (ft_strchr("><|;", *line))
			return (redir_separ(shell, line, res));
		else
			res = add_char(res, *line++);
	}
	shell->line_left = line;
	return (res);
}
