/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:34:24 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/15 21:07:50 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char		*ft_strjoin_with_slash(char const *s1, char const *s2)
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

static int		set_oldpwd(t_shell *shell)
{

}

int				ft_cd(t_shell *shell)
{
	char	*curpath;
	char	buf[PATH_MAX];
	int		ret;

	curpath = NULL;
	if (shell->start->argc == 0)
	{
		if (ft_strcmp(get_env(shell, "HOME"), "") == 0)
			ft_putstr_fd("cd: HOME not set", 1);
		else
			curpath = get_env(shell, "HOME");
	}
	else
		curpath = ft_strjoin_with_slash(getcwd(buf, 1024), shell->start->args[0]);
	printf("%s\n", curpath);
	ret = chdir(curpath);
	printf("%d\n", ret);
	return (0);
}
