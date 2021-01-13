/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:08:34 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/13 10:41:04 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		invitation(t_shell *shell)
{
	char *line;
	int i;

	i = 0;
	shell->command = ft_strdup("");
	shell->line_left = ft_strdup("");
	ft_putstr_fd("👻 \033[35mGhost'm IN i-Shell ⇥ \033[0m", 1);
	if (get_next_line(0, &line) < 0)
		ft_putstr_fd("Failed GNL\n", 2);
	if (!ft_strncmp("exit", (shell->command = ft_parcer(shell, line)), 4))
		return (0);
	printf("command: %s\n", shell->command);
	while(*shell->line_left)
	{
		shell->args = realloc_args(shell, i + 1);
		shell->args[i] = ft_strdup("");
		shell->args[i] = ft_strjoin(shell->args[i], \
									ft_parcer(shell, shell->line_left));
		printf("arg %d: %s\n", i, shell->args[i]);
		i++;
	}
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
