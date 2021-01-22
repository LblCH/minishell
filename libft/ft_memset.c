/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 20:14:30 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/22 19:41:33 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	char	*ptr;

	ptr = b;
	while (n > 0)
	{
		*ptr++ = (char)c;
		n--;
	}
	return (b);
}
