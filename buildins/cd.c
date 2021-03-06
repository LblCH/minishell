/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:34:24 by cdrennan          #+#    #+#             */
/*   Updated: 2021/03/06 06:00:03 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_pwd(t_shell *shell, char *pwd)
{
	char buf[PATH_MAX];
	char *env;

	env = ft_strjoin(pwd, getcwd(buf, PATH_MAX));
	if (env)
		add_env(shell, env);
	free(env);
	return (0);
}

int				error_handling(t_shell *shell)
{
	if (errno == ENOENT)
		error(shell->start->args[1], ": No such file or directory");
	else if (errno == EACCES)
		error(shell->start->args[1], ": Permission denied");
	else if (errno == ENOTDIR)
		error(shell->start->args[1], ": Not a directory");
	return (0);
}

char			*no_arg_cd(t_shell *shell, char *curpath)
{
	char *tmp;

	tmp = get_env(shell, "HOME");
	if (ft_strcmp(tmp, "") == 0)
		ft_putstr_fd("cd: HOME not set\n", 2);
	else
		curpath = ft_strdup(tmp);
	ft_free(tmp);
	return (curpath);
}

char			*special_args_cd(t_shell *shell, char *curpath)
{
	char	buf[PATH_MAX];
	char	*tmp;

	if (shell->start->args[1][0] == '/')
		curpath = ft_strdup(shell->start->args[1]);
	else if ((ft_strcmp(shell->start->args[1], "-") == 0))
	{
		tmp = get_env(shell, "OLDPWD");
		if (ft_strcmp(tmp, "") == 0)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			ft_free(tmp);
		}
		else
			curpath = tmp;
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

	curpath = NULL;
	ret = 1;
	if (!shell->start->args[1])
		curpath = no_arg_cd(shell, curpath);
	else
		curpath = special_args_cd(shell, curpath);
	set_pwd(shell, "OLDPWD=");
	if (curpath)
	{
		ret = chdir(curpath);
		if (ret < 0)
		{
			error_handling(shell);
			ret *= -1;
		}
		ft_free(curpath);
	}
	set_pwd(shell, "PWD=");
	return (ret);
}
