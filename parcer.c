/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 04:15:50 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/05 21:56:03 by cdrennan         ###   ########.fr       */
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
		{
			ft_putstr_fd(file, 2);
			ft_putendl_fd(": No such file or directory", 2);
			shell->err = 1;
			return (ft_strdup(""));
		}
	}
	else if (d_red == 0)
		shell->fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		shell->fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	free(file);
	file = NULL;
	return (line);
}

char		*spec_simbol(t_shell *shell, char *line, char **res)
{
	char *temp2;

	if (*line == '$')
	{
		if (!ft_isalnum(*(line + 1)) && !ft_strchr("\'\"?", *(line + 1)))
		{
			*res = add_char(*res, '$');
			line++;
		}
		else
		{
			if (*(++line) == '?')
			{
				temp2 = (shell->syntax) ? ft_itoa(shell->syntax) : ft_itoa(shell->ret);
				line++;
			}
			else
				temp2 = get_env(shell, line);
			while (ft_isalnum(*line) || *line == '_')
				line++;
			line = ft_strjoin(temp2, line);
			ft_free(temp2);
		}
	}
	else if (*line == '\\')
		line = escape_handler(++line, res);
	else if (*line == '\'' || *line == '\"')
		line = quotes_handler(shell, line, res, *line);
	else if (*line == '<' || *line == '>')
		line = redirect(shell, line, ft_strdup(""));
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
		if (ft_strchr("\'\"$\\><", *line))
			line = spec_simbol(shell, line, &res);
		else if (*line == '|')
		{
			line = separators(shell, line);
			if (*res)
				return (res);
			else
				return (NULL);
		}
		else if (*line == ';')
		{
			line++;
			shell->line_left = line;
			shell->semicol = 1;
			if (*res)
				return (res);
			else
			{
				ft_free(res);
				return (NULL);
			}
		}
		else
			res = add_char(res, *line++);
	}
	shell->line_left = line;
	return (res);
}
