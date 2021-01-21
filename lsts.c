/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:03:42 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/21 00:53:18 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 		add_token(t_shell *shell, t_token *token, char *line)
{
	int i;

	i = 1;
	printf("Adding token\n");
	token->command = ft_parcer(shell, line);
	printf("Command parced\n");
	token->args = realloc_args(token, 2);
	token->args[0] = ft_strdup(token->command);
	printf("command: %s %s\n", token->command, token->args[0]);
	while (ft_isspace(*shell->line_left))
		shell->line_left++;
	while(*shell->line_left)
	{
		token->args = realloc_args(token, i + 2);
		printf("args[0]:%s\n", token->args[0]);
		token->args[i] = ft_parcer(shell, shell->line_left);
		if (shell->fd_type == 1)
			token->fd_in = shell->fd;
		else if (shell->fd_type == -1)
			token->fd_out = shell->fd;
		while (ft_isspace(*shell->line_left))
			shell->line_left++;
		i++;
	}
	printf("Token added\n");
	printf("fd_in: %d fd_out: %d\n", token->fd_in, token->fd_out);
	i = 0;
	while (token->args && token->args[i] != NULL)
	{
		printf("arg %d: %s\n", i, token->args[i]);
		i++;
	}
}

t_token		*new_token(void)
{
	struct s_token *res;

	if (!(res = ft_calloc(1, sizeof(struct s_token))))
		return (NULL);
	res->command = ft_strdup("");
	res->next = NULL;
	res->fd_in = -1;
	res->fd_out = -1;
	res->is_piped = 0;
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
