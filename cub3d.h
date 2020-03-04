/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:12:09 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/04 10:22:32 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "./minilibx/mlx.h"
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include <stdio.h>

typedef struct	s_ind
{
	void	*img;
	int		*addr;
	int		he;
	int		wi;
	int		bits;
	int		line;
	int		endian;
}				t_ind;

typedef struct	s_sprpos
{
	double	x;
	double	y;
	double	udiv;
	double	vdiv;
	double	vmove;
	int		he;
	int		wi;
	int		*addr;
}				t_sprpos;

typedef struct	s_sprite
{
	t_sprpos	*p;
	int			numbers;
	double		*zbuff;
	int			*spriteo;
	double		*sprited;
}				t_sprite;

typedef struct	s_texture
{
	t_ind n;
	t_ind s;
	t_ind e;
	t_ind o;
	t_ind barrel;
}				t_texture;

typedef struct	s_self
{
	double posx;
	double posy;
	double dirx;
	double diry;
	double planex;
	double planey;
}				t_self;

typedef struct	s_move
{
	int forward;
	int backward;
	int right;
	int left;
	int rot_left;
	int rot_right;
}				t_move;

typedef struct	s_image
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct	s_parser
{
	int		h;
	int		w;
	int		mapwidth;
	int		mapheight;
	int		floor;
	int		ceiling;
	char	*n_t;
	char	*s_t;
	char	*w_t;
	char	*e_t;
	char	*spr_t;
	int		**worldmap;
}				t_parser;

typedef struct	s_ray
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		color;
	double	wallx;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
	t_ind	orient;
}				t_ray;

typedef struct	s_spray
{
	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	int		spritescreenx;
	int		vmovescreen;
	int		spriteheight;
	int		spritewidth;
	int		drawstarty;
	int		drawendy;
	int		drawstartx;
	int		drawendx;
	int		color;
	int		texx;
	int		texy;
}				t_spray;

typedef	struct	s_m
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_texture	text;
	t_self		self;
	t_move		move;
	t_image		image;
	t_sprite	spr;
	t_parser	parser;
	t_ray		ray;
	t_spray		spray;
}				t_m;

typedef struct	s_map
{
	int i;
	int j;
	int k;
}				t_map;

typedef struct	s_bmp
{
	unsigned char	*img;
	unsigned char	*bmpfileheader;
	unsigned char	*bmpinfoheader;
	unsigned char	*bmppad;
	int				filesize;
	int				y;
	int				i;
	int				j;
	int				fd;
}				t_bmp;

void			holy_diver(char *filename, t_m *s);
void			eagle_fly_free(char **split);
int				iron_man(t_m *s, char *line);
int				future_world(t_m *s, char *line);
int				move(t_m *s);
void			init_pos(t_m *s, int letter);
void			wall_raycasting(t_m *s);
void			wall_raycasting_init(t_m *s, int x);
void			wall_raycasting_hit(t_m *s);
void			wall_raycasting_step(t_m *s);
void			wall_raycasting_orientation(t_m *s);
void			sprite_raycasting(t_m *s);
void			sort_sprites(int *order, double *dist, int amount);
void			count_sprites(t_m *s);
int				deal_key(int key, t_m *params);
int				release_key(int key, t_m *params);
void			exit_game(t_m *s);
int				run_game(t_m *s);
int				destroy_window(t_m *s);
void			init_textures(t_m *s);
void			start_map(char *line, t_m *s);
int				**init_map(t_m *s);
int				map_max_height(t_m *s, char **split, char *line);
void			invalid_map(char *msg);
int				com_char(char c, int *dir);
void			flood_map(t_m *s, int i, int j, char **split);
void			liberate_map(t_m *s);
void			liberate_parse(t_m *s);
void			exit_game(t_m *s);
void			bmp(t_m *s, int *rimg);

#endif
