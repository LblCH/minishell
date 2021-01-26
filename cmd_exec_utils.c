/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 11:34:36 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/26 11:45:11 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_strjoin_with_slash(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	z;
	char	*res;

	i = 0;
	j = 0;
	z = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2)))
		return (NULL);
	while (s1[i])
		res[z++] = s1[i++];
	res[z] = '/';
	z++;
	while (s2[j])
		res[z++] = s2[j++];
	res[z] = '\0';
	return (res);
}

int			is_buildin(char *command)
{
	if (ft_strcmp(command, "echo") == 0 || ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0 || ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0 || ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

char		*check_location(char **paths, char *cmd)
{
	char *valid_path;
	DIR *dir;
	struct dirent *dir_content;
	int i;

	i = 0;
	while (paths[i++])
	{
		if(!(dir = opendir(paths[i])))
			return (NULL);
		dir_content = readdir(dir);
		while (dir_content)
		{
			if (ft_strcmp(dir_content->d_name, cmd) == 0)
			{
				valid_path = ft_strjoin_with_slash(paths[i], cmd);
				closedir(dir);
				return (valid_path);
			}
			dir_content = readdir(dir);
		}
	}
	closedir(dir);
	return (0);
}

void		sig_init()
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.ret = 0;
}