/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:03:42 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/26 16:12:11 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_token(t_shell *shell, t_token *token, char *line)
{
	int		i;
	char	*res;

	i = 0;
	shell->fd_type = 0;
//	printf("Adding token\n");
	while (ft_isspace(*line))
		line++;
	shell->line_left = line;
	while(*shell->line_left && shell->semicol != 1)
	{
		if (ft_strcmp((res = ft_parcer(shell, shell->line_left, "")), ""))
		{
			token->args = (char **)realloc_ptr(token->args, i + 2);
			token->args[i + 1] = NULL;
			token->args[i] = ft_strdup(res);
		}
		while (ft_isspace(*shell->line_left))
			shell->line_left++;
		i++;
	}
	if (shell->fd_type == 1)
		token->fd_out = shell->fd;
	else if (shell->fd_type == -1)
		token->fd_in = shell->fd;
	shell->fd = -1;
	shell->fd_type = 0;
//	printf("--------------\nToken added\n");
//	printf("fd_in: %d fd_out: %d\n", token->fd_in, token->fd_out);
//	i = 0;
//	while (token->args && token->args[i])
//	{
//		printf("arg %d: %s\n", i, token->args[i]);
//		i++;
//	}
//	printf("--------------\n");
}

t_token		*new_token(void)
{
	struct s_token *res;

	if (!(res = (t_token *)ft_calloc(1, sizeof(struct s_token))))
		return (NULL);
//	res->command = ft_strdup("");
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
