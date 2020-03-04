/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:59:24 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/03 10:14:15 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		run_game(t_m *s)
{
	move(s);
	wall_raycasting(s);
	sprite_raycasting(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->image.img, 0, 0);
	return (0);
}

void	init_pos2(t_m *s, int letter)
{
	if (letter == 'E')
	{
		s->self.dirx = 0;
		s->self.diry = 1;
		s->self.planex = 0.66;
		s->self.planey = 0;
	}
	if (letter == 'W')
	{
		s->self.dirx = 0;
		s->self.diry = -1;
		s->self.planex = -0.66;
		s->self.planey = 0;
	}
}

void	init_pos(t_m *s, int letter)
{
	if (letter == 'N')
	{
		s->self.dirx = -1;
		s->self.diry = 0;
		s->self.planex = 0;
		s->self.planey = 0.66;
	}
	if (letter == 'S')
	{
		s->self.dirx = 1;
		s->self.diry = 0;
		s->self.planex = 0;
		s->self.planey = -0.66;
	}
	init_pos2(s, letter);
}
