/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 09:31:04 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/04 10:28:56 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	eagle_fly_free(char **split)
{
	int i;

	i = 0;
	while (split[i] != 0)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	future_world2(t_m *s, char *line)
{
	char	**comma;

	if ((line[0] == 'F' && s->parser.floor) ||
			(line[0] == 'C' && s->parser.ceiling)
			|| line[1] != ' ')
	{
		liberate_parse(s);
		free(line);
		invalid_map("Invalid element");
	}
	comma = ft_split(line, ',');
	if (line[0] == 'F')
		s->parser.floor = (ft_atoi(comma[0] + 1) << 16) |
			(ft_atoi(comma[1]) << 8) | (ft_atoi(comma[2]));
	else
		s->parser.ceiling = (ft_atoi(comma[0] + 1) << 16) |
			(ft_atoi(comma[1]) << 8) | (ft_atoi(comma[2]));
	eagle_fly_free(comma);
}

int		future_world(t_m *s, char *line)
{
	char **split;

	if (line[0] == 'R')
	{
		if (s->parser.w || s->parser.h || line[1] != ' ')
		{
			free(line);
			liberate_parse(s);
			invalid_map("Invalid element");
		}
		split = ft_split(line, ' ');
		s->parser.w = ft_atoi(split[1]);
		s->parser.h = ft_atoi(split[2]);
		eagle_fly_free(split);
	}
	else if (line[0] == 'F' || line[0] == 'C')
		future_world2(s, line);
	else
	{
		liberate_parse(s);
		free(line);
		invalid_map("Invalid element");
	}
	return (1);
}
