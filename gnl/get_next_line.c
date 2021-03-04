/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 23:23:04 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/04 21:47:41 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_index(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] != (char)c)
		return (-1);
	return (i);
}

int		get_line(char *str, char **line, int i)
{
	*line = ft_substr_gnl(str, 0, i);
	++i;
	ft_memmove_gnl(str, str + i, (ft_strlen_gnl(str + i) + 1));
	return (1);
}

int		gnl_exit(int res, char *str)
{
	int ret;

	if (res == 0 && str[0] == 0)
	{
		ft_putstr_fd("\nexit\n", 2);
		exit(1);
	}
	else
		ret = 1;
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*str = NULL;
	int				res;
	int				i;

	if (!line || fd < 0 || BUFFER_SIZE < 1 || (read(fd, buff, 0) < 0))
		return (-1);
	if (str && (((i = find_index(str, '\n')) != -1)))
		return (get_line(str, line, i));
	res = 1;
	while (buff[0] != '\n' && res != 0)
	{
		res = read(fd, buff, BUFFER_SIZE);
		buff[res] = '\0';
		(res == 0 || buff[res - 1] != '\n') ? ft_putstr_fd("  \b\b", 1) : 0;
		str = add_and_free(str, buff);
		gnl_exit(res, str);
		if (((i = find_index(str, '\n')) != -1))
			return (get_line(str, line, i));
	}
	*line = (str) ? ft_strdup_gnl(str) : ft_strdup_gnl("");
	if (str)
		ft_free(str);
	return (res);
}
