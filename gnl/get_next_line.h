/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 23:49:35 by ztawanna          #+#    #+#             */
/*   Updated: 2021/01/27 13:03:03 by cdrennan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

int			get_next_line(int fd, char **line);
char		*add_and_free(char *s1, char *s2);
int			find_index(const char *s, int c);
int			get_line(char *str, char **line, int i);
char		*ft_substr_gnl(char const *s, int start, int len);
void		*ft_memmove_gnl(void *dst, const void *src, size_t len);
char		*ft_strdup_gnl(const char *s1);
size_t		ft_strlen_gnl(const char *s);

#endif
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif
