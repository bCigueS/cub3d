/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:54:53 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/30 11:50:50 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_cub3d *cub, t_pixel p)
{
	if ((p.x >= 0 || p.x < WINDOW_WIDTH) || (p.y >= 0 || p.y < WINDOW_HEIGHT))
		cub->img.addr[p.x + WINDOW_WIDTH * p.y] = p.color;
}

void	draw_background(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			draw_pixel(cub, (t_pixel){x, y, WHITE});
			x++;
		}
		y++;
	}
}

void	draw_rectangle(t_cub3d *cub,int tx, int ty, int size)
{
	int	x;
	int	y;

	y = ty;
	while (y < ty + size)
	{
		x = tx;
		while (x < tx + size)
		{
			draw_pixel(cub, (t_pixel){x, y, BLACK});
			x++;
		}
		y++;
	}
}

void	draw_map(t_cub3d *cub, int map[MH][MW])
{
	int x;
	int y;

	y = 0;
	while (y < MH)
	{
		x = 0;
		while (x < MW)
		{
			if (map[y][x] == 1)
				draw_rectangle(cub, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE);
			x++;
		}
		y++;
	}
}
