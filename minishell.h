/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 00:22:36 by ztawanna          #+#    #+#             */
/*   Updated: 2021/02/27 12:03:51 by cdrennan         ###   ########.fr       */
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
	char 			**args;
	int 			fd_in;
	int 			fd_out;
	int				fd_out_prev;
	struct s_token	*next;
}					t_token;

typedef struct		s_shell
{
	char			*line_left;
	char			**env;
	t_token			*start;
	int 			fd_type;
	int 			fd;
	int 			exit;
	int				semicol;
	uint8_t 		ret;
}					t_shell;

typedef struct		s_sig
{
	int				catched;
	pid_t			pid;
}					t_sig;

/*
 * minishell.c
 */
int					invitation(t_shell *shell);
void				clear_tokens(t_shell *shell);

/*
 * parcer.c
 */
char				*separators(t_shell *shell, char *line);
char				*redirect(t_shell *shell, char *line, char *file);
char				*ft_parcer(t_shell *shell, char *line, char *res);
char				*spec_simbol(t_shell *shell, char *line, char **res);

/*
 * preparcer.c
 */
int 				preparcer(char *line);

/*
 * utils.c
 */
char				*add_char(char *line, char c);
char				*escape_handler(char *line, char **res);
void				*realloc_ptr(char **ptr, size_t size);
char				*quotes_handler(t_shell *shell, char *line, char **res, char quote);
char				*get_env(t_shell *shell, char *env);

/*
 * buildins
 */

int 				ft_cd(t_shell *shell);
int					ft_echo(t_token *token);
int					ft_env(char **env);
void				ft_exit(t_shell *shell);
int					ft_export(t_shell *shell);
int					ft_pwd(void);
int					ft_unset(t_shell *shell, char *arg);


/*
 * lsts.c
 */
t_token				*new_token(void);
t_token				*token_last(t_token *token);
void 				add_token(t_shell *shell, t_token *token, char *line);

/*
 * command_run.c
 */

int					cmd_run(t_shell *shell, t_token *token);
void				prep_execve(t_shell *shell, t_token *token);
int 				start_execve(t_shell *shell);
int					error_execve(char *path);

/*
 * env_utils.c
 */

char				**sort_env(char **env, int y);
int					env_count(char **env);
char				*env_name(const char *src, char *dest);
int					add_env(t_shell *shell, char *arg);
void				error(char *env, char *text);

/*
 * cmd_exec_utils.c
 */

char				*ft_strjoin_with_slash(char const *s1, char const *s2);
int					is_buildin(char *command);
char				*check_location(char **paths, char *cmd);
int					cmd_run(t_shell *shell, t_token *token);

/*
 * signal.c
 */

void				catch_sig(int signal);
int					status_return(int status);
void				init();
extern				t_sig g_sig;

/*
 * export.c
 */

char				**create_env_array(char **env, char *to_add, int var);

/*
 * free_utils.c
 */

void				*ft_free(void *ptr);
void				free_tab(char **tab);

#endif
