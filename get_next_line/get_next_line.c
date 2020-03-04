/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:29:30 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/04 10:31:53 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		line_split(char **f, char **line, size_t n, int fd)
{
	char	*tmp1;

	*line = ft_substr(f[fd], 0, n);
	tmp1 = ft_substr(f[fd], n + 1, ft_strlen(f[fd]) - (n + 1));
	free(f[fd]);
	f[fd] = ft_strdup(tmp1);
	free(tmp1);
	return (1);
}

void	buffer_read(char *buff, char **f, int fd)
{
	char *tmp;

	if (!(f[fd]))
		f[fd] = ft_strdup(buff);
	else
	{
		tmp = ft_strjoin(f[fd], buff);
		free(f[fd]);
		f[fd] = ft_strdup(tmp);
		free(tmp);
	}
}

int		line_fill(char **f, char **line, int r, int fd)
{
	size_t	n;

	if (r < 0)
		return (-1);
	if (!f[fd] && r == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	n = 0;
	while (*(f[fd] + n) != '\n' && *(f[fd] + n) != 0)
		n++;
	if (*(f[fd] + n) == '\n')
		return (line_split(f, line, n, fd));
	*line = ft_strdup(f[fd]);
	free(f[fd]);
	f[fd] = NULL;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char		*buff;
	int			r;
	static char	*f[4096];

	if (fd < 0 || !line)
		return (-1);
	r = 0;
	if (f[fd] && ft_strchr(f[fd], '\n'))
		return (line_fill(f, line, r, fd));
	if (!(buff = (char *)malloc(sizeof(char) * (32 + 1))))
		return (-1);
	while ((r = read(fd, buff, 32)) > 0)
	{
		buff[r] = 0;
		buffer_read(buff, f, fd);
		if (ft_strchr(f[fd], '\n'))
			break ;
	}
	free(buff);
	return (line_fill(f, line, r, fd));
}
