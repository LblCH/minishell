/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 22:43:04 by ztawanna          #+#    #+#             */
/*   Updated: 2021/02/26 20:18:08 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}
