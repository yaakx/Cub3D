/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:34:59 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/04 10:38:24 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	main_init(t_m *s)
{
	s->move.backward = 0;
	s->move.forward = 0;
	s->move.rot_right = 0;
	s->move.rot_left = 0;
	s->move.right = 0;
	s->move.left = 0;
	s->mlx_ptr = mlx_init();
	s->image.img = mlx_new_image(s->mlx_ptr, s->parser.w, s->parser.h);
	s->image.addr = (int *)mlx_get_data_addr(s->image.img,
			&s->image.bits_per_pixel, &s->image.line_length, &s->image.endian);
	init_textures(s);
	count_sprites(s);
}

int		main(int argc, char **argv)
{
	t_m	s;

	if (argc < 2 || argc > 3 || (argc == 3 &&
				ft_strncmp(argv[2], "--save", 10)))
	{
		invalid_map("Argument error");
		exit(0);
	}
	holy_diver(argv[1], &s);
	main_init(&s);
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 6))
	{
		wall_raycasting(&s);
		sprite_raycasting(&s);
		bmp(&s, s.image.addr);
		exit_game(&s);
	}
	s.win_ptr = mlx_new_window(s.mlx_ptr, s.parser.w, s.parser.h, "mlx 42");
	mlx_hook(s.win_ptr, 2, 1l << 0, deal_key, &s);
	mlx_hook(s.win_ptr, 3, 1l << 1, release_key, &s);
	mlx_hook(s.win_ptr, 17, 1l << 5, destroy_window, &s);
	mlx_loop_hook(s.mlx_ptr, run_game, &s);
	mlx_loop(s.mlx_ptr);
}
