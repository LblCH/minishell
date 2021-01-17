/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:03:42 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/13 17:08:52 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 		add_token(t_shell *shell, t_token *token, char *line)
{
	int i;

	i = 0;
	token->command = ft_parcer(shell, line);
	printf("command: %s\n", token->command);
	while(*shell->line_left)
	{
		token->args = realloc_args(token, i + 1);
		token->args[i] = ft_strjoin("", \
											ft_parcer(shell, shell->line_left));
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