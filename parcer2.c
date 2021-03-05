/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 23:05:32 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/06 00:05:51 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*file_error(t_shell *shell, char *file)
{
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": No such file or directory", 2);
	shell->err = 1;
	return (ft_strdup(""));
}

char	*redir_separ(t_shell *shell, char *line, char *res)
{
	if (*line == '<' || *line == '>')
		shell->line_left = redirect(shell, line, ft_strdup(""));
	else if (*line == '|')
		shell->line_left = separators(shell, line);
	else if (*line == ';')
	{
		line++;
		shell->line_left = line;
		shell->semicol = 1;
	}
	if (*res)
		return (res);
	else
	{
		ft_free(res);
		return (NULL);
	}
}

char	*variable_add(t_shell *shell, char *line)
{
	char	*temp2;
	char	*temp;

	if (*(++line) == '?')
	{
		temp2 = (shell->syntax) ? ft_itoa(shell->syntax) : \
														ft_itoa(shell->ret);
		line++;
	}
	else
		temp2 = get_env(shell, line);
	while (ft_isalnum(*line) || *line == '_')
		line++;
	temp = line;
	line = ft_strjoin(temp2, line);
	ft_free(temp);
	ft_free(temp2);
	return (line);
}
