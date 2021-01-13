/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 05:48:10 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/13 10:48:14 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**realloc_args(t_shell *shell, int i)
{
	char	**new;

	if (!(new = (char **) malloc(i)))
		return (NULL);
	if (shell->args)
		new = shell->args;
	return (new);
}

char		*escape_handler(char *line, char **res)
{
	char s[2];

	s[1] = '\0';
	if (ft_strchr(";\\\'\"><|", *line))
	{
		s[0] = *line;
		*res = ft_strjoin(*res, s);
		line++;
	}
	return (line);
}

char		*quotes_handler(t_shell *shell, char *line, char **res, char quote)
{
	char s[2];

	s[1] = '\0';
	while (*(++line) && *line != quote)
	{
		s[0] = *line;
		if (ft_strchr("$\\", *line) && quote == '\"')
		{
			line = spec_simbol(shell, line, res) - 1;
		}
		else
			*res = ft_strjoin(*res, s);
	}
	if (*line == quote)
		line++;
	else
		ft_putstr_fd("Non couple quotes.\n", 2);
	return (line);
}

char		*get_env(t_shell *shell, char *env)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while(ft_isalnum(env[i]) || env[i] == '_')
	{
		len++;
		i++;
	}
	i = 0;
	while(shell->env[i])
	{
		if (!ft_strncmp(env, shell->env[i], len) \
			&& shell->env[i][len] == '=')
			return (&shell->env[i][len + 1]);
		i++;
	}
	return ("");
}