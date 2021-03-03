/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:00:01 by cdrennan          #+#    #+#             */
/*   Updated: 2021/02/26 21:44:46 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**sort_env(char **env, int y)
{
	int		x;
	char	*tmp;
	int		sorted;

	sorted = 0;
	while (env && sorted == 0)
	{
		sorted = 1;
		x = 0;
		while (x < y - 1)
		{
			if (ft_strcmp(env[x], env[x + 1]) > 0)
			{
				tmp = env[x];
				env[x] = env[x + 1];
				env[x + 1] = tmp;
				sorted = 0;
			}
			x++;
		}
		y--;
	}
	return (env);
}

int			env_count(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char		*env_name(const char *src, char *dest)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '=';
	dest[i + 1] = '\0';
	return (dest);
}

int			add_env(t_shell *shell, char *arg)
{
	int		i;
	char	*name;
	char	**tmp;

	i = 0;
	name = ft_calloc(1, ft_strlen(arg));
	name = env_name(arg, name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0)
		{
			ft_free(shell->env[i]);
			shell->env[i] = ft_strdup(arg);
			ft_free(name);
			return (0);
		}
		i++;
	}
	ft_free(name);
	tmp = shell->env;
	shell->env = create_env_array(tmp, arg, 1);
	free_tab(tmp);
	return (0);
}

void		error(char *env, char *text)
{
	ft_putstr_fd(env, 2);
	ft_putendl_fd(text, 2);
}
