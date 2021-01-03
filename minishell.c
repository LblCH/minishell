/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:08:34 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/03 07:23:35 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	shell.env = envp;
	ft_putstr_fd("💀 \033[36miMiNishell ⇥ \033[0m", 1);
	ft_parcer(&shell);
	printf("\n%s\n", shell.command);
	return (0);
}
