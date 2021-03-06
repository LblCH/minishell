/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 05:48:10 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/06 06:31:50 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*add_char(char *line, char c)
{
	char	*temp;
	int		i;

	i = 0;
	if (!(temp = (char *)malloc(sizeof(char) * ft_strlen(line) + 2)))
		exit(9);
	while (line && line[i])
	{
		temp[i] = line[i];
		i++;
	}
	temp[i] = c;
	temp[i + 1] = '\0';
	(line) ? free(line) : (0);
	line = NULL;
	return (temp);
}

void		*realloc_ptr(char **ptr, size_t size)
{
	char	**new;
	int		j;

	j = 0;
	if (!(new = ft_calloc(size + 1, sizeof(char *))))
		return (NULL);
	if (ptr)
	{
		while (ptr[j])
		{
			(new[j] = ft_strdup(ptr[j])) ? 0 : exit(9);
			free(ptr[j]);
			j++;
		}
		free(ptr);
		ptr = NULL;
	}
	return (new);
}

char		*escape_handler(char *line, char **res)
{
//	char *temp;

//	printf("%c\n", *line);
	if (ft_strchr(";\\\'\"><| $", *line))
	{
//		temp = *res;
		*res = add_char(*res, *line);
//		free(temp);
		line++;
	}
	return (line);
}

char		*quotes_handler(t_shell *shell, char *line, char **res, char quote)
{
	while (*(++line) && *line != quote)
	{
		if (ft_strchr("$\\", *line) && quote == '\"' )
			line = spec_simbol(shell, line, res) - 1;
		else
			*res = add_char(*res, *line);
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
	while (ft_isalnum(env[i]) || env[i] == '_')
	{
		len++;
		i++;
	}
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(env, shell->env[i], len) \
			&& shell->env[i][len] == '=')
			return (ft_strdup(&shell->env[i][len + 1]));
		i++;
	}
	return (ft_strdup(""));
}
