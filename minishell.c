/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:08:34 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/25 19:44:47 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_tokens(t_shell *shell)
{
	t_token	*tmp;
	t_token	*previous;
	int i;

//	printf("---------------------------------\nClearing tokens\n");
	tmp = shell->start;
	while (tmp)
	{
		i = 0;
		//(tmp->command) ? free(tmp->command) : 0;
		previous = tmp;
		while (tmp->args && tmp->args[i])
		{
			free(tmp->args[i]);
//			printf("args[%d] cleared\n", i);
			i++;
		}
//		printf("args cleared\n");
		(tmp->args) ? free(tmp->args) : 0;
		(tmp->fd_in > 0) ? close(tmp->fd_in) : 0;
		(tmp->fd_out > 0) ? close(tmp->fd_out) : 0;
		tmp = tmp->next;
		free(previous);
	}
	shell->start = NULL;
//	printf("Tokens cleared\n-----------------------------------\n");
}

int		invitation(t_shell *shell)
{
	char *line;

	while (shell->exit == 0)
	{
		shell->line_left = ft_strdup("");
		shell->fd = -1;
		ft_putstr_fd("👻 \033[35mGhost'm IN i-Shell ⇥ \033[0m", 1);
		if (get_next_line(0, &line) < 0)
			ft_putstr_fd("Failed GNL\n", 2);
		if (!shell->start)
			shell->start = new_token();
		(*line)	? add_token(shell, shell->start, line) : 0;
		cmd_run(shell);
		clear_tokens(shell);
		free(line);
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	shell.env = envp;
	shell.env_export = envp;
	shell.ret = 0;
	shell.exit = 0;
	shell.start = NULL;
	invitation(&shell);
	return (shell.ret);
}
