/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:49:23 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/27 13:03:03 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_shell *shell, char *arg)
{
	int i;

	i = 0;
	if (!arg)
		return (0);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], arg, ft_strlen(arg)) == 0)
		{
			shell->env[i] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}
