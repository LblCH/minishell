/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrennan <cdrennan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:49:23 by cdrennan          #+#    #+#             */
/*   Updated: 2021/01/15 23:28:10 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_shell *shell, char *arg)
{
	int i;

	i = 0;
	if (shell->start->argc < 1)
		return (0);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], arg, ft_strlen(arg)) == 0)
		{
			shell->env[i] = NULL;
			shell->env_export[i] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}
