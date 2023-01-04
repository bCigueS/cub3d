/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:54:53 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/04 16:12:07 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_img img, t_pixel p)
{
	int	size;

	size = WINDOW_WIDTH * img.ratio;
	if ((p.x >= 0 && p.x < WINDOW_WIDTH * img.ratio) && \
			(p.y >= 0 && p.y < WINDOW_HEIGHT * img.ratio))
		img.addr[p.x + size * p.y] = p.color;
}

void	draw_background(t_img img)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT * img.ratio)
	{
		x = 0;
		while (x < WINDOW_WIDTH * img.ratio)
		{
			draw_pixel(img, (t_pixel){x, y, WHITE});
			x++;
		}
		y++;
	}
}

void	draw_rectangle(t_img img, int tx, int ty, int size)
{
	int	x;
	int	y;

	y = ty;
	while (y < ty + size)
	{
		x = tx;
		while (x < tx + size)
		{
			draw_pixel(img, (t_pixel){x, y, BLACK});
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
	while (y < MH)
	{
		x = 0;
		while (x < MW)
		{
			if (cub->map[y][x] == 1)
				draw_rectangle(cub->mini_map, \
						x * TILE_SIZE * cub->mini_map.ratio, \
						y * TILE_SIZE * cub->mini_map.ratio, \
						TILE_SIZE * cub->mini_map.ratio);
			x++;
		}
		y++;
	}
}
