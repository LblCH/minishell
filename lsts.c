/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:03:42 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/21 00:12:51 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 		add_token(t_shell *shell, t_token *token, char *line)
{
	int i;

	i = 0;
	token->command = ft_parcer(shell, line);
	while (ft_isspace(*shell->line_left))
		shell->line_left++;
	while(*shell->line_left)
	{
		token->args = realloc_args(token, i + 1);
		token->args[i] = ft_parcer(shell, shell->line_left);
		if (shell->fd_type == 1)
			token->fd_in = shell->fd;
		else if (shell->fd_type == -1)
			token->fd_out = shell->fd;
		while (ft_isspace(*shell->line_left))
			shell->line_left++;
		i++;
	}
	printf("command: %s \n", token->command);
	printf("fd_in: %d fd_out: %d\n", token->fd_in, token->fd_out);
	i = 0;
	while (token->args && token->args[i])
	{
		printf("arg %d: %s\n", i, token->args[i]);
		i++;
	}
}

t_token		*new_token(void)
{
	struct s_token *res;

	if(!(res = malloc(sizeof(struct s_token))))
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