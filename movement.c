/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:21:43 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/03 12:08:55 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	m_forward_backward(t_m *s, double movespeed, int i)
{
	if (i == 1)
	{
		if (s->parser.worldmap[(int)(s->self.posx + s->self.dirx *
					movespeed)][(int)(s->self.posy)] != 1)
			s->self.posx += s->self.dirx * movespeed;
		if (s->parser.worldmap[(int)(s->self.posx)][(int)(s->self.posy
					+ s->self.diry * movespeed)] != 1)
			s->self.posy += s->self.diry * movespeed;
	}
	else
	{
		if (s->parser.worldmap[(int)(s->self.posx - s->self.dirx
					* movespeed)][(int)(s->self.posy)] != 1)
			s->self.posx -= s->self.dirx * movespeed;
		if (s->parser.worldmap[(int)(s->self.posx)][(int)(s->self.posy
					- s->self.diry * movespeed)] != 1)
			s->self.posy -= s->self.diry * movespeed;
	}
}

void	m_right_left(t_m *s, double movespeed, int i)
{
	if (i == 0)
	{
		if (s->parser.worldmap[(int)(s->self.posx - s->self.diry *
					movespeed)][(int)(s->self.posy)] != 1)
			s->self.posx -= s->self.diry * movespeed;
		if (s->parser.worldmap[(int)(s->self.posx)][(int)(s->self.posy
					+ s->self.dirx * movespeed)] != 1)
			s->self.posy += s->self.dirx * movespeed;
	}
	else
	{
		if (s->parser.worldmap[(int)(s->self.posx + s->self.diry
					* movespeed)][(int)(s->self.posy)] != 1)
			s->self.posx += s->self.diry * movespeed;
		if (s->parser.worldmap[(int)(s->self.posx)][(int)(s->self.posy
					- s->self.dirx * movespeed)] != 1)
			s->self.posy -= s->self.dirx * movespeed;
	}
}

void	m_rot_left(t_m *s, double rotspeed)
{
	double olddirx;
	double oldplanex;

	olddirx = s->self.dirx;
	s->self.dirx = s->self.dirx * cos(rotspeed)
		- s->self.diry * sin(rotspeed);
	s->self.diry = olddirx * sin(rotspeed) +
		s->self.diry * cos(rotspeed);
	oldplanex = s->self.planex;
	s->self.planex = s->self.planex * cos(rotspeed)
		- s->self.planey * sin(rotspeed);
	s->self.planey = oldplanex * sin(rotspeed)
		+ s->self.planey * cos(rotspeed);
}

void	m_rot_right(t_m *s, double rotspeed)
{
	double olddirx;
	double oldplanex;

	olddirx = s->self.dirx;
	s->self.dirx = s->self.dirx * cos(-rotspeed)
		- s->self.diry * sin(-rotspeed);
	s->self.diry = olddirx * sin(-rotspeed) +
		s->self.diry * cos(-rotspeed);
	oldplanex = s->self.planex;
	s->self.planex = s->self.planex * cos(-rotspeed)
		- s->self.planey * sin(-rotspeed);
	s->self.planey = oldplanex * sin(-rotspeed)
		+ s->self.planey * cos(-rotspeed);
}

int		move(t_m *s)
{
	double movespeed;
	double rotspeed;

	movespeed = 0.1;
	rotspeed = 0.04;
	if ((s->move.forward ^ s->move.backward) && (s->move.right ^ s->move.left))
		movespeed = movespeed / 2;
	else if (s->move.left || s->move.right)
		movespeed = movespeed / 1.5;
	if (s->move.forward)
		m_forward_backward(s, movespeed, 1);
	if (s->move.backward)
		m_forward_backward(s, movespeed, 0);
	if (s->move.right)
		m_right_left(s, movespeed, 1);
	if (s->move.left)
		m_right_left(s, movespeed, 0);
	if (s->move.rot_right)
		m_rot_right(s, rotspeed);
	if (s->move.rot_left)
		m_rot_left(s, rotspeed);
	return (0);
}
