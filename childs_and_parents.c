/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_and_parents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 13:14:39 by cdrennan          #+#    #+#             */
/*   Updated: 2021/02/27 13:16:35 by cdrennan         ###   ########.fr       */
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

int			buildin_or_child(t_shell *shell, t_token *token, int ret)
{
	if (token->args && (!ft_strcmp(token->args[0], "exit")))
	{
		ft_exit(shell);
		return (shell->ret);
	}
	else if (token->args && (is_buildin(token->args[0])))
		ret = run_buildin(shell, token->args[0]);
	else
	{
		g_sig.pid = fork();
		if (g_sig.pid == 0)
		{
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
	return (ret);
}