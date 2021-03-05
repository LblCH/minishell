/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 23:05:32 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/05 23:05:32 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*file_error(t_shell *shell, char *file)
{
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": No such file or directory", 2);
	shell->err = 1;
	return (ft_strdup(""));
}

