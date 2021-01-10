/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 05:48:10 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/10 14:41:57 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*quotes_handler(t_shell *shell, char *line, char **res, char quote)
{
	char s[2];

	s[1] = '\0';
	while(*(++line) && *line != quote)
	{
		s[0] = *line;
		if (*line == '$' && quote == '\"')
			line = spec_simbol(shell, line, res);
		else
			*res = ft_strjoin(*res, s);
	}
	if(*line == quote)
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