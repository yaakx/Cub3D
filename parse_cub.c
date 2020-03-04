/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 09:30:30 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/04 10:32:49 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_holy(t_m *s)
{
	s->parser.n_t = NULL;
	s->parser.s_t = NULL;
	s->parser.e_t = NULL;
	s->parser.w_t = NULL;
	s->parser.spr_t = NULL;
	s->parser.h = 0;
	s->parser.w = 0;
	s->parser.mapwidth = 0;
	s->parser.mapheight = 0;
	s->parser.floor = 0;
	s->parser.ceiling = 0;
}

char	*holy_diver2(char *line, int fd)
{
	char	*tmp;
	char	*tmp2;
	char	*map;
	int		i;

	map = ft_strjoin(line, "\n");
	free(line);
	while ((i = get_next_line(fd, &line)) == 1)
	{
		if (line[0] == 0)
		{
			free(map);
			invalid_map("Empty line in the map");
		}
		tmp2 = ft_strjoin(map, line);
		tmp = ft_strjoin(tmp2, "\n");
		free(tmp2);
		free(map);
		map = tmp;
		free(line);
	}
	return (map);
}

void	holy_diver3(char *line, int *element, t_m *s)
{
	if (line[0] == 'S' || line[0] == 'N' ||
			line[0] == 'W' || line[0] == 'E')
		if (iron_man(s, line))
			*element += 1;
	if (line[0] == 'R' || line[0] == 'C' || line[0] == 'F')
		if (future_world(s, line))
			*element += 1;
	free(line);
	line = NULL;
}

void	holy_diver4(int element, char *line, t_m *s, int fd)
{
	char *map;

	if (element < 8)
	{
		free(line);
		liberate_parse(s);
		invalid_map("Not all elemets");
	}
	map = holy_diver2(line, fd);
	close(fd);
	start_map(map, s);
}

void	holy_diver(char *filename, t_m *s)
{
	int		fd;
	char	*line;
	int		i;
	int		element;

	init_holy(s);
	element = 0;
	fd = open(filename, O_RDONLY);
	while ((i = get_next_line(fd, &line)) == 1)
	{
		if (line[0] == 0)
		{
			free(line);
			continue ;
		}
		if (element == 8)
			break ;
		if (ft_isdigit(line[0]))
			break ;
		holy_diver3(line, &element, s);
	}
	holy_diver4(element, line, s, fd);
}
