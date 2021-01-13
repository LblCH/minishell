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