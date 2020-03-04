/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:09:21 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/03 11:46:05 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_errors(t_m *s, char **split)
{
	int i;
	int j;

	if (s->self.posx == 0)
	{
		eagle_fly_free(split);
		liberate_parse(s);
		liberate_map(s);
		invalid_map("Not starting position");
	}
	flood_map(s, (int)s->self.posx, (int)s->self.posy, split);
	i = 0;
	while (i < s->parser.mapwidth)
	{
		j = 0;
		while (j < s->parser.mapheight)
		{
			if (s->parser.worldmap[i][j] == 3)
				s->parser.worldmap[i][j] = 0;
			else if (s->parser.worldmap[i][j] == 4)
				s->parser.worldmap[i][j] = 2;
			j++;
		}
		i++;
	}
}

void	create_map_utils(t_m *s, char *split, t_map *t)
{
	if (*split == 'N' || *split == 'S' ||
			*split == 'E' || *split == 'W')
	{
		s->self.posx = t->i + 0.5;
		s->self.posy = t->k + 0.5;
		init_pos(s, *split);
		*split = '0';
	}
	if (*split != 0 && *split != ' ')
	{
		s->parser.worldmap[t->i][t->k] = *split - 48;
		t->k++;
		t->j++;
	}
	else if (*split == ' ')
		t->j++;
	else
	{
		s->parser.worldmap[t->i][t->k] = 0;
		t->k++;
	}
}

void	create_map(t_m *s, char **split)
{
	t_map t;

	t.i = 0;
	s->parser.worldmap = init_map(s);
	while (split[t.i] != 0)
	{
		t.j = 0;
		t.k = 0;
		while (t.k < s->parser.mapheight)
			create_map_utils(s, &split[t.i][t.j], &t);
		t.i++;
	}
	map_errors(s, split);
}

void	start_map(char *line, t_m *s)
{
	char	**split;

	s->parser.mapwidth = 0;
	split = ft_split(line, '\n');
	while (split[s->parser.mapwidth] != 0)
		s->parser.mapwidth++;
	s->parser.mapheight = map_max_height(s, split, line);
	create_map(s, split);
	free(line);
}
