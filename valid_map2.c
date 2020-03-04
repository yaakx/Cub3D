/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 09:51:43 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/03 11:11:53 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		com_char(char c, int *dir)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*dir == 1)
			return (0);
		else
		{
			*dir = *dir + 1;
			return (1);
		}
	}
	else if (c == ' ' || c == '1' || c == '2' || c == '0')
		return (1);
	return (0);
}

void	max_height_utils(char **split, char *line, t_m *s)
{
	eagle_fly_free(split);
	free(line);
	liberate_parse(s);
	invalid_map("Duplicate intial position");
}

int		map_max_height(t_m *s, char **split, char *line)
{
	int	max_h;
	int i;
	int j;
	int	h;
	int dir;

	max_h = 0;
	i = 0;
	dir = 0;
	while (split[i] != 0)
	{
		h = 0;
		j = 0;
		while (split[i][j] != 0)
		{
			if (!com_char(split[i][j], &dir))
				max_height_utils(split, line, s);
			if (split[i][j] != ' ')
				h++;
			j++;
		}
		i++;
		max_h = (h > max_h) ? h : max_h;
	}
	return (max_h);
}

int		**init_map(t_m *s)
{
	int **map;
	int i;

	i = 0;
	map = (int **)malloc(sizeof(int *) * s->parser.mapwidth);
	while (i < s->parser.mapwidth)
	{
		map[i] = (int *)malloc(sizeof(int) * s->parser.mapheight);
		i++;
	}
	return (map);
}

void	flood_map(t_m *s, int i, int j, char **split)
{
	if (i >= s->parser.mapwidth || j >= s->parser.mapheight || j < 0 || i < 0)
	{
		eagle_fly_free(split);
		liberate_parse(s);
		liberate_map(s);
		invalid_map("Not closed map");
	}
	else if (s->parser.worldmap[i][j] != 1 && s->parser.worldmap[i][j] != 3
			&& s->parser.worldmap[i][j] != 4)
	{
		s->parser.worldmap[i][j] = (s->parser.worldmap[i][j] == 2) ? 4 : 3;
		flood_map(s, i + 1, j, split);
		flood_map(s, i, j + 1, split);
		flood_map(s, i - 1, j, split);
		flood_map(s, i, j - 1, split);
	}
}
