/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 09:29:36 by jcorral-          #+#    #+#             */
/*   Updated: 2020/02/27 09:29:38 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_raycasting_perwall(t_m *s)
{
	s->ray.perpwalldist = (s->ray.side == 0) ? (s->ray.mapx -
			s->self.posx + (1 - s->ray.stepx) / 2) / s->ray.raydirx :
		(s->ray.mapy - s->self.posy + (1 - s->ray.stepy) / 2) / s->ray.raydiry;
	s->ray.lineheight = (int)(s->parser.h / s->ray.perpwalldist);
	s->ray.drawstart = (-s->ray.lineheight / 2 + s->parser.h / 2 < 0) ? 0
		: -s->ray.lineheight / 2 + s->parser.h / 2;
	s->ray.drawend = (s->ray.lineheight / 2 + s->parser.h / 2 >= s->parser.h)
		? s->parser.h - 1 : s->ray.lineheight / 2 + s->parser.h / 2;
}

void	wall_raycasting_draw(t_m *s, int x)
{
	int y;

	y = 0;
	while (y < s->ray.drawstart)
	{
		s->image.addr[y * s->parser.w + x] = s->parser.ceiling;
		y++;
	}
	while (y < s->ray.drawend)
	{
		s->ray.texy = (int)s->ray.texpos & (s->ray.orient.he - 1);
		s->ray.texpos += s->ray.step;
		s->ray.color = s->ray.orient.addr[s->ray.orient.he *
			s->ray.texy + s->ray.texx];
		if (s->ray.side == 1)
			s->ray.color = (s->ray.color >> 1) & 8355711;
		s->image.addr[y * s->parser.w + x] = s->ray.color;
		y++;
	}
	while (y < s->parser.h)
	{
		s->image.addr[y * s->parser.w + x] = s->parser.floor;
		y++;
	}
}

void	wall_raycasting_text(t_m *s)
{
	if (s->ray.side == 0)
		s->ray.wallx = s->self.posy + s->ray.perpwalldist * s->ray.raydiry;
	else
		s->ray.wallx = s->self.posx + s->ray.perpwalldist * s->ray.raydirx;
	s->ray.wallx -= floor((s->ray.wallx));
	s->ray.texx = (int)(s->ray.wallx * (double)(s->ray.orient.wi));
	if (s->ray.side == 0 && s->ray.raydirx > 0)
		s->ray.texx = s->ray.orient.wi - s->ray.texx - 1;
	if (s->ray.side == 1 && s->ray.raydiry < 0)
		s->ray.texx = s->ray.orient.wi - s->ray.texx - 1;
	s->ray.step = 1.0 * s->ray.orient.he
		/ s->ray.lineheight;
	s->ray.texpos = (s->ray.drawstart - s->parser.h / 2
			+ s->ray.lineheight / 2) * s->ray.step;
}

void	wall_raycasting(t_m *s)
{
	int x;

	x = 0;
	while (x < s->parser.w)
	{
		wall_raycasting_init(s, x);
		wall_raycasting_step(s);
		wall_raycasting_hit(s);
		wall_raycasting_perwall(s);
		wall_raycasting_orientation(s);
		wall_raycasting_text(s);
		wall_raycasting_draw(s, x);
		s->spr.zbuff[x] = s->ray.perpwalldist;
		x++;
	}
}
