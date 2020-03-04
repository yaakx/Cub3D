/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorral- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:56:42 by jcorral-          #+#    #+#             */
/*   Updated: 2020/03/03 16:25:42 by jcorral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

void	bmp_infoheader(t_bmp *b, t_m *s)
{
	b->bmpfileheader = (unsigned char *)malloc(14);
	b->bmpinfoheader = (unsigned char *)malloc(40);
	ft_memset(b->bmpfileheader, 0, 16);
	ft_memset(b->bmpinfoheader, 0, 40);
	b->bmpfileheader[0] = 'B';
	b->bmpfileheader[1] = 'M';
	b->bmpfileheader[2] = (unsigned char)(b->filesize);
	b->bmpfileheader[3] = (unsigned char)(b->filesize >> 8);
	b->bmpfileheader[4] = (unsigned char)(b->filesize >> 16);
	b->bmpfileheader[5] = (unsigned char)(b->filesize >> 24);
	b->bmpfileheader[10] = 54;
	b->bmpinfoheader[0] = 40;
	b->bmpinfoheader[12] = 1;
	b->bmpinfoheader[14] = 24;
	b->bmpinfoheader[4] = (unsigned char)(s->parser.w);
	b->bmpinfoheader[5] = (unsigned char)(s->parser.w >> 8);
	b->bmpinfoheader[6] = (unsigned char)(s->parser.w >> 16);
	b->bmpinfoheader[7] = (unsigned char)(s->parser.w >> 24);
	b->bmpinfoheader[8] = (unsigned char)(s->parser.h);
	b->bmpinfoheader[9] = (unsigned char)(s->parser.h >> 8);
	b->bmpinfoheader[10] = (unsigned char)(s->parser.h >> 16);
	b->bmpinfoheader[11] = (unsigned char)(s->parser.h >> 24);
	b->bmppad = (unsigned char *)malloc(3);
	ft_memset(b->bmppad, 0, 3);
}

void	fill_bmp(t_bmp *b, t_m *s)
{
	b->fd = open("saved_img/img.bmp", O_TRUNC | O_CREAT | O_RDWR, 0666);
	write(b->fd, b->bmpfileheader, 14);
	write(b->fd, b->bmpinfoheader, 40);
	b->i = 0;
	while (b->i < s->parser.h)
	{
		write(b->fd, b->img + (s->parser.w *
					(s->parser.h - b->i - 1) * 3), 3 * s->parser.w);
		write(b->fd, b->bmppad, (4 - (s->parser.w * 3) % 4) % 4);
		b->i++;
	}
	free(b->img);
	free(b->bmpfileheader);
	free(b->bmpinfoheader);
	free(b->bmppad);
	close(b->fd);
}

void	bmp(t_m *s, int *rimg)
{
	t_bmp	b;

	b.filesize = 54 + 3 * s->parser.w * s->parser.h;
	b.img = (unsigned char *)malloc(3 * s->parser.w * s->parser.h);
	b.i = 0;
	while (b.i < s->parser.w)
	{
		b.j = 0;
		while (b.j < s->parser.h)
		{
			b.y = (s->parser.h - 1) - b.j;
			b.img[(b.i + b.y * s->parser.w) * 3 + 2] = (unsigned char)
				(rimg[b.i + b.y * s->parser.w] >> 16);
			b.img[(b.i + b.y * s->parser.w) * 3 + 1] = (unsigned char)
				((rimg[b.i + b.y * s->parser.w] << 16) >> 24);
			b.img[(b.i + b.y * s->parser.w) * 3] = (unsigned char)
				((rimg[b.i + b.y * s->parser.w] << 24) >> 24);
			b.j++;
		}
		b.i++;
	}
	bmp_infoheader(&b, s);
	fill_bmp(&b, s);
}
