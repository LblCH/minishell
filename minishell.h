/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 00:22:36 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/21 00:53:18 by ztawanna         ###   ########.fr       */
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
	int 			is_piped;
	int 			fd_in;
	int 			fd_out;
	struct s_token	*next;
}					t_token;

typedef struct		s_shell
{
	char			*line_left;
	char			**env;
	char 			**env_export;
	t_token			*start;
	int 			fd_type;
	int 			fd;
	int 			exit;
	uint8_t 		ret;
}					t_shell;

/*
 * minishell.c
 */
int			invitation(t_shell *shell);

/*
 * parcer.c
 */
char		*separators(t_shell *shell, char *line);
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
 * buildins
 */

int 		ft_cd(t_shell *shell);
int			ft_echo(t_token *token);
int			ft_env(char **env);
void		ft_exit(t_shell *shell);
int			ft_export(t_shell *shell);
int			ft_pwd(void);
int			ft_unset(t_shell *shell, char *arg);


/*
 * lsts.c
 */
t_token		*new_token(void);
t_token		*token_last(t_token *token);
void 		add_token(t_shell *shell, t_token *token, char *line);

/*
 * command_run.c
 */

void		cmd_run(t_shell *shell);

/*
 * env_utils.c
 */

char		**sort_env(char **env, int y);
int			env_count(char **env);
char		*env_name(const char *src, char *dest);
int			add_env(t_shell *shell, char *arg);
void		error_printing(char *env, char *text);

/*
 * cmd_exec_utils.c
 */

char		*ft_strjoin_with_slash(char const *s1, char const *s2);
int			is_buildin(char *command);
char		*check_location(char **paths, char *cmd);

#endif