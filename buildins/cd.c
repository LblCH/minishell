/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:34:24 by cdrennan          #+#    #+#             */
/*   Updated: 2021/02/27 18:17:42 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_pwd(t_shell *shell, char *pwd)
{
	char buf[PATH_MAX];
	char *env;

	env = ft_strjoin(pwd, getcwd(buf, PATH_MAX));
	add_env(shell, env);
	free(env);
	return (0);
}

int				error_handling(t_shell *shell)
{
	if (errno == ENOENT)
		error(shell->start->args[1], "No such file or directory: ");
	else if (errno == EACCES)
		error(shell->start->args[1], "Permission denied: ");
	else if (errno == ENOTDIR)
		error(shell->start->args[1], "Not a directory: ");
	return (0);
}

char			*no_arg_cd(t_shell *shell, char *curpath)
{
	if (ft_strcmp(get_env(shell, "HOME"), "") == 0)
		ft_putstr_fd("cd: HOME not set\n", 2);
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
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		else
			curpath = get_env(shell, "OLDPWD");
	}
	else
		curpath =
				ft_strjoin_with_slash(getcwd(buf, 1024), shell->start->args[1]);
	return (curpath);
}

int				ft_cd(t_shell *shell)
{
	char	*curpath;
	int		ret;
	int		free_me;

	curpath = NULL;
	free_me = 0;
	if (!shell->start->args[1])
		curpath = no_arg_cd(shell, curpath);
	else
	{
		curpath = special_args_cd(shell, curpath);
		free_me = 1;
	}
	set_pwd(shell, "OLDPWD=");
	if ((ret = chdir(curpath)) < 0)
	{
		error_handling(shell);
		ret *= -1;
	}
	set_pwd(shell, "PWD=");
	if (free_me)
		free(curpath);
	return (ret);
}
