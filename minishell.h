/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 00:22:36 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/13 15:20:44 by ztawanna         ###   ########.fr       */
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

typedef struct		s_token
{
	char 			*command;
	char 			**args;
	struct s_token	*next;
}					t_token;

typedef struct		s_shell
{
	char			*line_left;
	char			**env;
	t_token			*start;
}					t_shell;

/*
 * minishell.c
 */
int			invitation(t_shell *shell);

/*
 * parcer.c
 */
char		*ft_parcer(t_shell *shell, char *line);
char		*spec_simbol(t_shell *shell, char *line, char **res);
void 		add_token(t_shell *shell, t_token *token, char *line);

/*
 * utils.c
 */
char		*escape_handler(char *line, char **res);
char		**realloc_args(t_token *token, int i);
char		*quotes_handler(t_shell *shell, char *line, char **res, char quote);
char		*get_env(t_shell *shell, char *env);
t_token		*new_token(void);

/*
 * buildin.c
 */

/*
 *
 */
#endif