/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:09:32 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/03 13:34:26 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	liberate_parse(t_m *s)
{
	if (s->parser.s_t)
		free(s->parser.s_t);
	if (s->parser.n_t)
		free(s->parser.n_t);
	if (s->parser.w_t)
		free(s->parser.w_t);
	if (s->parser.e_t)
		free(s->parser.e_t);
	if (s->parser.spr_t)
		free(s->parser.spr_t);
}

void	liberate_map(t_m *s)
{
	int i;

	i = 0;
	while (i < s->parser.mapwidth)
	{
		free(s->parser.worldmap[i]);
		i++;
	}
	free(s->parser.worldmap);
}

void	exit_game(t_m *s)
{
	free(s->spr.p);
	free(s->spr.zbuff);
	free(s->spr.spriteo);
	free(s->spr.sprited);
	liberate_parse(s);
	liberate_map(s);
	exit(0);
}

void	invalid_map(char *msg)
{
	int i;

	write(1, "Error\n", 6);
	i = 0;
	while (msg[i] != 0)
	{
		write(1, &msg[i], 1);
		i++;
	}
	write(1, "\n", 1);
	exit(0);
}
