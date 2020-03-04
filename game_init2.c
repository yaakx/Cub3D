/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:31:07 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/04 14:19:22 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_m *s)
{
	s->text.n.img = mlx_xpm_file_to_image(s->mlx_ptr,
			s->parser.n_t, &s->text.n.he, &s->text.n.wi);
	s->text.s.img = mlx_xpm_file_to_image(s->mlx_ptr,
			s->parser.s_t, &s->text.s.he, &s->text.s.wi);
	s->text.e.img = mlx_xpm_file_to_image(s->mlx_ptr,
			s->parser.w_t, &s->text.e.he, &s->text.e.wi);
	s->text.o.img = mlx_xpm_file_to_image(s->mlx_ptr,
			s->parser.e_t, &s->text.o.he, &s->text.o.wi);
	s->text.barrel.img = mlx_xpm_file_to_image(s->mlx_ptr,
			s->parser.spr_t, &s->text.barrel.he, &s->text.barrel.wi);
	s->text.n.addr = (int *)mlx_get_data_addr(s->text.n.img,
			&s->text.n.bits, &s->text.n.line, &s->text.n.endian);
	s->text.s.addr = (int *)mlx_get_data_addr(s->text.s.img,
			&s->text.s.bits, &s->text.s.line, &s->text.s.endian);
	s->text.e.addr = (int *)mlx_get_data_addr(s->text.e.img,
			&s->text.e.bits, &s->text.e.line, &s->text.e.endian);
	s->text.o.addr = (int *)mlx_get_data_addr(s->text.o.img,
			&s->text.o.bits, &s->text.o.line, &s->text.o.endian);
	s->text.barrel.addr = (int *)mlx_get_data_addr(s->text.barrel.img,
			&s->text.barrel.bits, &s->text.barrel.line, &s->text.barrel.endian);
}

int		destroy_window(t_m *s)
{
	exit_game(s);
	return (0);
}
