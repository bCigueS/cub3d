/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:54:53 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/23 10:42:40 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_cub3d *cub, t_pixel p, int option)
{
	int		size;
	int		window_width;
	int		window_height;
	t_img	img;

	if (option == WINDOW)
	{
		window_width = WINDOW_WIDTH;
		window_height = WINDOW_HEIGHT;
		img = cub->img;
	}
	else
	{
		window_width = cub->info.map_dim_w;
		window_height = cub->info.map_dim_h;
		img = cub->mmap;
	}
	size = window_width * img.ratio;
	if ((p.x >= 0 && p.x < window_width * img.ratio) && \
			(p.y >= 0 && p.y < window_height * img.ratio))
		img.addr[p.x + size * p.y] = p.color;
}

void	draw_background(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->info.map_dim_h * cub->mmap.ratio)
	{
		x = 0;
		while (x < cub->info.map_dim_w * cub->mmap.ratio)
		{
			draw_pixel(cub, (t_pixel){x, y, WHITE}, MINI_MAP);
			x++;
		}
		y++;
	}
}

void	draw_rectangle(t_cub3d *cub, int tx, int ty, int size)
{
	int	x;
	int	y;

	y = ty;
	while (y < ty + size)
	{
		x = tx;
		while (x < tx + size)
		{
			draw_pixel(cub, (t_pixel){x, y, BLACK}, MINI_MAP);
			x++;
		}
		y++;
	}
}

void	draw_map(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->info.map_dim_h * cub->mmap.ratio)
	{
		x = 0;
		while (x < cub->info.map_dim_w * cub->mmap.ratio)
		{
			if (is_a_wall(cub, x / cub->mmap.ratio, y / cub->mmap.ratio))
				draw_pixel(cub, \
						(t_pixel){x, y, BLACK}, \
						MINI_MAP);
			x++;
		}
		y++;
	}
}

void	draw_ceiling_floor(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
				draw_pixel(cub, (t_pixel){x, y, CEILLING}, WINDOW);
			else
				draw_pixel(cub, (t_pixel){x, y, FLOOR}, WINDOW);
			x++;
		}
		y++;
	}
}
