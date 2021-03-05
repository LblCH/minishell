/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_and_parents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 13:14:39 by cdrennan          #+#    #+#             */
/*   Updated: 2021/03/04 23:47:39 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			child_process(t_shell *shell, t_token *token)
{
	int ret;

	if (token->fd_in != -1)
	{
		dup2(token->fd_in, 0);
		(token->fd_out_prev != -1) ? close(token->fd_out_prev) : 0;
	}
	if (token->fd_out != -1)
	{
		dup2(token->fd_out, 1);
		if (token->next)
			(token->next->fd_in != -1) ? close(token->next->fd_in) : 0;
	}
	ret = cmd_run(shell, token);
	return (ret);
}

void increment_shell_level (t_shell *shell)
{
	char	*res;
	char 	*res2;
	char 	*res3;

	res3 = get_env(shell, "SHLVL");
	res = ft_itoa(ft_atoi(res3) + 1);
	res2 = ft_strjoin("SHLVL=", res);
	add_env(shell, res2);
	ft_free(res);
	ft_free(res2);
	ft_free(res3);
}



int			buildin_or_child(t_shell *shell, t_token *token, int ret)
{
	if (token->args && (!ft_strcmp(token->args[0], "exit")))
	{
		ft_exit(shell);
		return (shell->ret);
	}
	else if (token->args && (is_buildin(token->args[0])))
		ret = run_buildin(shell, token->args[0], token);
	else
	{
		g_sig.pid = fork();
		if (g_sig.pid == 0)
		{
			if (!ft_strcmp(token->args[0], "./minishell"))
				increment_shell_level(shell);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			signal(SIGTERM, SIG_DFL);
			ret = child_process(shell, token);
		}
	}
	return (ret);
}

int			parent(int ret)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	wait(&ret);
	signal(SIGQUIT, catch_sig);
	signal(SIGINT, catch_sig);
	ret = status_return(ret);
	return(ret);
}
