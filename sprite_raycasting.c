/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 09:50:02 by jcorral-          #+#    #+#             */
/*   Updated: 2020/02/27 11:54:21 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_raycasting_calsc2(t_m *s, int i)
{
	if (s->spray.drawstarty < 0)
		s->spray.drawstarty = 0;
	s->spray.drawendy = s->spray.spriteheight / 2 + s->parser.h / 2 +
		s->spray.vmovescreen;
	if (s->spray.drawendy >= s->parser.h)
		s->spray.drawendy = s->parser.h - 1;
	s->spray.spritewidth = abs((int)(s->parser.h /
				(s->spray.transformy))) / s->spr.p[i].udiv;
	s->spray.drawstartx = (-s->spray.spritewidth / 2 + s->spray.spritescreenx <
			0) ? 0 : -s->spray.spritewidth / 2 + s->spray.spritescreenx;
	s->spray.drawendx = (s->spray.spritewidth / 2 + s->spray.spritescreenx
		>= s->parser.w) ? s->parser.w - 1 : s->spray.spritewidth / 2
		+ s->spray.spritescreenx;
}

void	sprite_raycasting_calc(t_m *s, int i)
{
	s->spray.spritex = s->spr.p[s->spr.spriteo[i]].x - s->self.posx;
	s->spray.spritey = s->spr.p[s->spr.spriteo[i]].y - s->self.posy;
	s->spray.invdet = 1.0 / (s->self.planex * s->self.diry -
			s->self.dirx * s->self.planey);
	s->spray.transformx = s->spray.invdet * (s->self.diry *
			s->spray.spritex - s->self.dirx * s->spray.spritey);
	s->spray.transformy = s->spray.invdet * (-s->self.planey *
			s->spray.spritex + s->self.planex * s->spray.spritey);
	s->spray.spritescreenx = (int)((s->parser.w / 2) *
			(1 + s->spray.transformx / s->spray.transformy));
	s->spray.vmovescreen = (int)(s->spr.p[i].vmove / s->spray.transformy);
	s->spray.spriteheight = abs((int)(s->parser.h /
				(s->spray.transformy))) / s->spr.p[i].vdiv;
	s->spray.drawstarty = -s->spray.spriteheight / 2 + s->parser.h
		/ 2 + s->spray.vmovescreen;
	sprite_raycasting_calsc2(s, i);
}

void	sprite_raycasting_draw2(t_m *s, int stripe, t_sprpos p)
{
	int		y;
	int		d;
	double	di;
	double	sh;

	y = s->spray.drawstarty;
	sh = (double)p.he / (double)s->spray.spriteheight / (double)256;
	di = -s->parser.h * 128 + s->spray.spriteheight * 128;
	di = di * sh;
	sh = sh * 256;
	di = di - s->spray.vmovescreen * sh;
	while (y < s->spray.drawendy)
	{
		s->spray.texy = (double)(y * (double)sh) + (double)di;
		d = p.wi * s->spray.texy + s->spray.texx;
		s->spray.color = p.addr[d];
		if (s->spray.color != 0)
			s->image.addr[y * s->parser.w + stripe] = s->spray.color;
		y++;
	}
}

void	sprite_raycasting_draw(t_m *s, int i)
{
	int stripe;

	stripe = s->spray.drawstartx;
	while (stripe < s->spray.drawendx)
	{
		s->spray.texx = (int)(256 * (stripe - (-s->spray.spritewidth / 2
						+ s->spray.spritescreenx)) *
				s->spr.p[s->spr.spriteo[i]].wi / s->spray.spritewidth) / 256;
		if (s->spray.transformy > 0 && stripe > 0 && stripe
				< s->parser.w && s->spray.transformy < s->spr.zbuff[stripe])
			sprite_raycasting_draw2(s, stripe, s->spr.p[s->spr.spriteo[i]]);
		stripe++;
	}
}

void	sprite_raycasting(t_m *s)
{
	int i;

	i = 0;
	while (i < s->spr.numbers)
	{
		s->spr.spriteo[i] = i;
		s->spr.sprited[i] = ((s->self.posx - s->spr.p[i].x)
				* (s->self.posx - s->spr.p[i].x) +
				(s->self.posy - s->spr.p[i].y) *
				(s->self.posy - s->spr.p[i].y));
		i++;
	}
	sort_sprites(s->spr.spriteo, s->spr.sprited, s->spr.numbers);
	i = 0;
	while (i < s->spr.numbers)
	{
		sprite_raycasting_calc(s, i);
		sprite_raycasting_draw(s, i);
		i++;
	}
}
