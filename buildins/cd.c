/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:34:24 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/16 11:26:30 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



static int		set_pwd(t_shell *shell, char* pwd)
{
	char buf[PATH_MAX];
	char *env;

	env = ft_strjoin(pwd, getcwd(buf, PATH_MAX));
	add_env(shell, env);
	return (0);
}

int error_handling (t_shell *shell)
{
	if (errno == 2)
		error_printing(shell->start->args[0],
					   "No such file or directory: ");
	else if (errno == 13)
		error_printing(shell->start->args[0],
					   "Permission denied: ");
	return (0);
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
	set_pwd(shell, "OLDPWD=");
	if ((ret = chdir(curpath) < 0))
	{
		error_handling(shell);
		return (1);
	}
	printf("%d\n%d\n", ret, errno);
	set_pwd(shell, "PWD=");
	return (0);
}
