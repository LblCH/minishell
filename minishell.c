/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:08:34 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/10 12:43:00 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int invitation(t_shell *shell)
{
	char *line;

	shell->command = ft_strdup("");
	ft_putstr_fd("👻 \033[35mGhost'm IN i-Shell ⇥ \033[0m", 1);
	if(get_next_line(0, &line) < 0)
		ft_putstr_fd("Failed GNL\n", 2);
	if(!ft_strncmp("exit", (shell->command = ft_parcer(shell, line)), 4))
		return (0);
	invitation(shell);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	shell.env = envp;
	invitation(&shell);
	return (0);
}
