/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:03:42 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/06 05:55:31 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_token(t_shell *shell, t_token *token, char *line)
{
	int		i;
	char	*res;

	i = 0;
	shell->fd_type = 0;
	while (ft_isspace(*line))
		line++;
	shell->line_left = line;
	while (shell->line_left && *shell->line_left && shell->semicol != 1)
	{
		res = ft_parcer(shell, shell->line_left);
		if (res)
		{
			(token->args = (char **)realloc_ptr(token->args, i + 2)) ? \
			0 : exit(9);
			token->args[i + 1] = NULL;
			(token->args[i]) ? free(token->args[i]) : 0;
			!(token->args[i] = ft_strdup(res)) ? exit(9) : 0;
			i++;
		}
		while (shell->line_left && ft_isspace(*shell->line_left))
			shell->line_left++;
		ft_free(res);
	}
}

t_token		*new_token(void)
{
	struct s_token *res;

	if (!(res = (t_token *)ft_calloc(1, sizeof(struct s_token))))
		return (NULL);
	res->next = NULL;
	res->fd_in = -1;
	res->fd_out = -1;
	res->fd_out_prev = -1;
	return (res);
}

t_token		*token_last(t_token *token)
{
	if (token)
	{
		while (token->next != NULL)
			token = token->next;
	}
	return (token);
}

void		correct_fds(t_shell *shell, t_token *token)
{
	if (shell->fd_type == 1)
		token->fd_out = shell->fd;
	else if (shell->fd_type == -1)
		token->fd_in = shell->fd;
	shell->fd = -1;
	shell->fd_type = 0;
}
