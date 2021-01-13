/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:34:24 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/12 10:54:45 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strjoin_with_slash(char const *s1, char const *s2)
{
	size_t i;
	size_t j;
	size_t z;
	char *res;

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

int ft_cd (t_shell *shell)
{
	char *curpath = NULL;
	char buf[PATH_MAX];
	int ret;

	if (!(shell->start->args[0]))
	{
		if (ft_strcmp(get_env(shell, "HOME"), "") == 0)
			ft_putstr_fd("cd: HOME not set", 1);
		else
			curpath = get_env(shell, "HOME");
	}
	else
		curpath = shell->start->args[0];

	curpath = ft_strjoin_with_slash(getcwd(buf, 1024), curpath);
	printf("%s\n", curpath);
	ret = chdir(curpath);
	printf("%d\n", ret);
	return (0);
}