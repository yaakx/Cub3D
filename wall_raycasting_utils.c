/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycasting_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 09:29:54 by jcorral-          #+#    #+#             */
/*   Updated: 2020/02/27 09:29:55 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_raycasting_init(t_m *s, int x)
{
	s->ray.camerax = 2 * x / (double)s->parser.w - 1;
	s->ray.raydirx = s->self.dirx + s->self.planex * s->ray.camerax;
	s->ray.raydiry = s->self.diry + s->self.planey * s->ray.camerax;
	s->ray.mapx = (int)s->self.posx;
	s->ray.mapy = (int)s->self.posy;
	s->ray.deltadistx = fabs(1 / s->ray.raydirx);
	s->ray.deltadisty = fabs(1 / s->ray.raydiry);
	s->ray.hit = 0;
}

void	wall_raycasting_hit(t_m *s)
{
	while (s->ray.hit == 0)
	{
		if (s->ray.sidedistx < s->ray.sidedisty)
		{
			s->ray.sidedistx += s->ray.deltadistx;
			s->ray.mapx += s->ray.stepx;
			s->ray.side = 0;
		}
		else
		{
			s->ray.sidedisty += s->ray.deltadisty;
			s->ray.mapy += s->ray.stepy;
			s->ray.side = 1;
		}
		if (s->parser.worldmap[s->ray.mapx][s->ray.mapy] == 1)
			s->ray.hit = 1;
	}
}

void	wall_raycasting_step(t_m *s)
{
	if (s->ray.raydirx < 0)
	{
		s->ray.stepx = -1;
		s->ray.sidedistx = (s->self.posx - s->ray.mapx) * s->ray.deltadistx;
	}
	else
	{
		s->ray.stepx = 1;
		s->ray.sidedistx = (s->ray.mapx + 1.0 -
				s->self.posx) * s->ray.deltadistx;
	}
	if (s->ray.raydiry < 0)
	{
		s->ray.stepy = -1;
		s->ray.sidedisty = (s->self.posy - s->ray.mapy) * s->ray.deltadisty;
	}
	else
	{
		s->ray.stepy = 1;
		s->ray.sidedisty = (s->ray.mapy + 1.0 -
				s->self.posy) * s->ray.deltadisty;
	}
}

void	wall_raycasting_orientation(t_m *s)
{
	if (s->self.posx > (double)s->ray.mapx)
	{
		if (s->ray.side == 1 && s->self.posy > s->ray.mapy)
			s->ray.orient = s->text.o;
		else if (s->ray.side == 1 && s->self.posy < s->ray.mapy)
			s->ray.orient = s->text.e;
		else
			s->ray.orient = s->text.s;
	}
	else
	{
		if (s->ray.side == 1 && s->self.posy > s->ray.mapy)
			s->ray.orient = s->text.o;
		else if (s->ray.side == 1 && s->self.posy < s->ray.mapy)
			s->ray.orient = s->text.e;
		else
			s->ray.orient = s->text.n;
	}
}
