/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 23:03:35 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/15 21:07:50 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
	{
		ft_putendl_fd(buf, 1);
		return (0);
	}
	else
		return (1);
}
