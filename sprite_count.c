/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_count_load.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:03:01 by jcorral-          #+#    #+#             */
/*   Updated: 2020/02/27 13:19:19 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(int *order, double *dist, int amount)
{
	int		i;
	int		j;
	int		a;
	double	b;

	i = 0;
	while (i < (amount - 1))
	{
		j = 0;
		while (j < (amount - 1 - i))
		{
			if (dist[j] < dist[j + 1])
			{
				b = dist[j + 1];
				dist[j + 1] = dist[j];
				dist[j] = b;
				a = order[j + 1];
				order[j + 1] = order[j];
				order[j] = a;
			}
			j++;
		}
		i++;
	}
}

void	map_load_sprites(t_m *s, int i, int n)
{
	int j;

	while (i < s->parser.mapwidth)
	{
		j = 0;
		while (j < s->parser.mapheight)
		{
			if (s->parser.worldmap[i][j] == 2)
			{
				s->spr.p[n].x = i + 0.5;
				s->spr.p[n].y = j + 0.5;
				s->spr.p[n].addr = s->text.barrel.addr;
				s->spr.p[n].he = s->text.barrel.he;
				s->spr.p[n].wi = s->text.barrel.wi;
				s->spr.p[n].udiv = 1;
				s->spr.p[n].vdiv = 1;
				s->spr.p[n].vmove = 0.0;
				n = n + 1;
			}
			j++;
		}
		i++;
	}
}

void	count_sprites(t_m *s)
{
	int i;
	int n;
	int j;

	n = 0;
	i = 0;
	while (i < s->parser.mapwidth)
	{
		j = 0;
		while (j < s->parser.mapheight)
		{
			if (s->parser.worldmap[i][j] == 2)
				n = n + 1;
			j++;
		}
		i++;
	}
	s->spr.numbers = n;
	s->spr.p = (t_sprpos *)malloc(sizeof(t_sprpos) * n);
	s->spr.zbuff = (double *)malloc(sizeof(double) * s->parser.w);
	s->spr.spriteo = (int *)malloc(sizeof(int) * n);
	s->spr.sprited = (double *)malloc(sizeof(double) * n);
	map_load_sprites(s, 0, 0);
}
