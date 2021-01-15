/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:08:34 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/15 21:07:44 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		invitation(t_shell *shell)
{
	char *line;

	while (shell->exit == 0)
	{
		shell->line_left = ft_strdup("");
		ft_putstr_fd("👻 \033[35mGhost'm IN i-Shell ⇥ \033[0m", 1);
		if (get_next_line(0, &line) < 0)
			ft_putstr_fd("Failed GNL\n", 2);
		if (!shell->start)
			shell->start = new_token();
		add_token(shell, shell->start, line);
		free(line);
		cmd_run(shell);
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	shell.env = envp;
	shell.env_export = shell.env;
	shell.ret = 0;
	shell.exit = 0;
	invitation(&shell);
	return (shell.ret);
}
