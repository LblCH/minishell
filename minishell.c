/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:08:34 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/06 01:52:35 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig g_sig;

void	clear_tokens(t_shell *shell)
{
	t_token		*tmp;
	t_token		*temp;
	int			i;

	tmp = shell->start;
	while (tmp)
	{
		i = 0;
		while (tmp->args && tmp->args[i])
		{
			free(tmp->args[i]);
			tmp->args[i] = NULL;
			i++;
		}
		(tmp->args && tmp->args[i]) ? free(tmp->args[i]) : 0;
		(tmp->args) ? free(tmp->args) : 0;
		tmp->args = NULL;
		(tmp->fd_in > 0) ? close(tmp->fd_in) : 0;
		(tmp->fd_out > 0) ? close(tmp->fd_out) : 0;
		tmp->fd_out_prev = -1;
		temp = tmp->next;
		ft_free(tmp);
		tmp = temp;
	}
	shell->start = NULL;
}

void	parce_exec(t_shell *shell, char *line)
{
	shell->ret = (g_sig.catched == 1) ? 1 : shell->ret;
	if (!shell->start)
		shell->start = new_token();
	(*line) ? add_token(shell, shell->start, line) : 0;
	(shell->err != 1 && shell->start->args) ?
			shell->ret = start_execve(shell) : 0;
	while (shell->semicol == 1 && shell->exit != 1 && shell->err != 1)
	{
		shell->semicol = 0;
		if (!shell->start)
			shell->start = new_token();
		if (*shell->line_left)
			add_token(shell, shell->start, shell->line_left);
		shell->ret = start_execve(shell);
	}
	shell->syntax = 0;
}

int		invitation(t_shell *shell)
{
	char *line;

	while (shell->exit == 0)
	{
		ft_putstr_fd("👻 \033[35mGhost'm IN i-Shell ⇥ \033[0m", 1);
		init(shell);
		shell->line_added = ft_strdup("");
		signal(SIGQUIT, catch_sig);
		signal(SIGINT, catch_sig);
		if (get_next_line(0, &line) < 0)
		{
			ft_putstr_fd("\nGNL error\n", 2);
			exit(1);
		}
		if (line && preparcer(line) == 0)
			parce_exec(shell, line);
		else
			shell->syntax = 258;
		ft_free(line);
		ft_free(shell->line_added);
		clear_tokens(shell);
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	shell.env = create_env_array(envp, NULL, 0);
	shell.exit = 0;
	shell.fd = -1;
	shell.start = NULL;
	shell.semicol = 0;
	increment_shell_level(&shell);
	invitation(&shell);
	return (shell.syntax ? shell.syntax : shell.ret);
}
