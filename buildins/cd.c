/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:34:24 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/27 13:51:47 by cdrennan         ###   ########.fr       */
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
	if (errno == ENOENT)
		error_printing(shell->start->args[1],
					   "No such file or directory: ");
	else if (errno == EACCES)
		error_printing(shell->start->args[1],
					   "Permission denied: ");
	else if (errno == ENOTDIR)
		error_printing(shell->start->args[1],
					   "Not a directory: ");
	return (0);
}
char			*no_arg_cd(t_shell *shell, char *curpath)
{
	if (ft_strcmp(get_env(shell, "HOME"), "") == 0)
		ft_putstr_fd("cd: HOME not set", 2);
	else
		curpath = get_env(shell, "HOME");
	return (curpath);
}

char			*special_args_cd(t_shell *shell, char *curpath)
{
	char	buf[PATH_MAX];

	if (shell->start->args[1][0] == '/')
		curpath = shell->start->args[1];
	else if ((ft_strcmp(shell->start->args[1], "-") == 0))
	{
		if (ft_strcmp(get_env(shell, "OLDPWD"), "") == 0)
			ft_putstr_fd("cd: OLDPWD not set", 2);
		else
			curpath = get_env(shell, "OLDPWD");
	}
	else
		curpath = ft_strjoin_with_slash(getcwd(buf, 1024), shell->start->args[1]);
	return (curpath);
}

int				ft_cd(t_shell *shell)
{
	char	*curpath;
	int		ret;

	curpath = NULL;
	if (!shell->start->args[1])
		curpath = no_arg_cd(shell, curpath);
	else
		curpath = special_args_cd(shell, curpath);
	set_pwd(shell, "OLDPWD=");
	if ((ret = chdir(curpath)) < 0)
	{
		error_handling(shell);
		ret *= -1;
	}
	set_pwd(shell, "PWD=");
	return (ret);
}
