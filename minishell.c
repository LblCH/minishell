/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:08:34 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/20 23:34:43 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		invitation(t_shell *shell)
{
	char *line;

	shell->line_left = ft_strdup("");
	shell->fd = -1;
	ft_putstr_fd("👻 \033[35mGhost'm IN i-Shell ⇥ \033[0m", 1);
	if (get_next_line(0, &line) < 0)
		ft_putstr_fd("Failed GNL\n", 2);
	if (!shell->start)
		shell->start = new_token();
	(*line)	? add_token(shell, shell->start, line) : 0;
	if (!ft_strncmp("exit", (shell->start->command), 4))
		return (0);
	free(line);
	invitation(shell);
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	shell.env = envp;
	invitation(&shell);
	return (0);
}
