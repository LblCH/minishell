/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 00:22:36 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/10 13:37:50 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"

typedef struct		s_shell
{
	char 			*command;
	char 			*args;
	char			**env;
}					t_shell;

char		*ft_parcer(t_shell *shell, char *line);
int			invitation(t_shell *shell);
char		*spec_simbol(t_shell *shell, char *line, char **res);
int			quotes_cl(char *line);
char		*quotes_handler(t_shell *shell, char *line, char **res, char quote);
char		*get_env(t_shell *shell, char *env);

#endif