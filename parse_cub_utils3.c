/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 09:33:47 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/04 10:22:26 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	iron_man2(t_m *m, char **s, char *line, int i)
{
	char **split;

	if (*s || line[i] != ' ')
	{
		liberate_parse(m);
		free(line);
		invalid_map("Invalid element");
	}
	split = ft_split(line, ' ');
	*s = ft_strdup(split[1]);
	eagle_fly_free(split);
}

int		iron_man(t_m *s, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		iron_man2(s, &s->parser.n_t, line, 2);
	else if (line[0] == 'S' && line[1] == 'O')
		iron_man2(s, &s->parser.s_t, line, 2);
	else if (line[0] == 'E' && line[1] == 'A')
		iron_man2(s, &s->parser.e_t, line, 2);
	else if (line[0] == 'W' && line[1] == 'E')
		iron_man2(s, &s->parser.w_t, line, 2);
	else if (line[0] == 'S')
		iron_man2(s, &s->parser.spr_t, line, 1);
	else
	{
		liberate_parse(s);
		free(line);
		invalid_map("Invalid element");
	}
	return (1);
}
