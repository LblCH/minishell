/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 00:22:36 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/19 23:21:23 by ztawanna         ###   ########.fr       */
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
	int 			fd_in;
	int 			fd_out;
	struct s_token	*next;
}					t_token;

typedef struct		s_shell
{
	char			*line_left;
	char			**env;
	t_token			*start;
	int 			fd_type;
	int 			fd;
}					t_shell;

/*
 * minishell.c
 */
int			invitation(t_shell *shell);

/*
 * parcer.c
 */
char		*redirect(t_shell *shell, char *line);
char		*ft_parcer(t_shell *shell, char *line);
char		*spec_simbol(t_shell *shell, char *line, char **res);


/*
 * utils.c
 */
char		*add_char(char *line, char c);
char		*escape_handler(char *line, char **res);
char		**realloc_args(t_token *token, int i);
char		*quotes_handler(t_shell *shell, char *line, char **res, char quote);
char		*get_env(t_shell *shell, char *env);

/*
 * pipe_utils.c
 */
char		*add_pipe(t_shell *shell, char *line);

/*
 * lsts.c
 */
t_token		*new_token(void);
t_token		*token_last(t_token *token);
void 		add_token(t_shell *shell, t_token *token, char *line);

#endif