/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:54:53 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/02 15:45:18 by sbeylot          ###   ########.fr       */
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

void	draw_grid(t_cub3d *cub)
{
	int x;
	int y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		draw_line(cub, init_line(init_pixel(0, y, BLACK), \
			init_pixel(WINDOW_WIDTH, y, BLACK)));
		y += TILE_SIZE;
	}
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		draw_line(cub, init_line(init_pixel(x, 0, BLACK), \
			init_pixel(x, WINDOW_HEIGHT, BLACK)));
		x += TILE_SIZE;
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

void	draw_rectangle2(t_cub3d *cub,int tx, int ty)
{
	int	x;
	int	y;

	y = ty - 3;
	while (y < ty  + 3)
	{
		x = tx - 3;
		while (x < tx + 3)
		{
			draw_pixel(cub, (t_pixel){x, y, RED});
			x++;
		}
		y++;
	}
}
void	draw_map(t_cub3d *cub)
{
	int x;
	int y;

	y = 0;
	while (y < MH)
	{
		x = 0;
		while (x < MW)
		{
			if (cub->map[y][x] == 1)
				draw_rectangle(cub, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE);
			x++;
		}
		y++;
	}
}
