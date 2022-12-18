/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:28:30 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/18 19:48:26 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Drawing a pixel --- 
 *	Check if pixel is out of bound, if not, draw pixel at the rigth adress
 *	pix.x + WINDOW_WIDTH * pix.y allow me to find the address of the 
 *	corresponding pixel
 *	Drawing a pixel --- 
 */
void	draw_pixel(t_cub3d *cub, t_pixel pix)
{
	if ((pix.x >= 0 && pix.x < WINDOW_WIDTH)
			&& (pix.y >= 0 && pix.y < WINDOW_HEIGHT))
		cub->img.addr[pix.x + WINDOW_WIDTH * pix.y] = pix.color;
}

/*	Drawing the background ---
 *	To draw the background, i need to fill every pixel of the img
 */

void	draw_rectangle(t_cub3d *cub, int posx, int posy, int size)
{
	int x;
	int y;

	y = posy;
	while (y < posy + size)
	{
		x = posx;
		while (x < posx + size)
		{
			draw_pixel(cub, (t_pixel){x, y, BLACK});
			x++;
		}
		y++;
	}
}

void	draw_wall(t_cub3d *cub)
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
				draw_rectangle(cub, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE);
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

void	draw_background(t_cub3d *cub)
{
	int x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			draw_pixel(cub, (t_pixel){x, y, 0xFFFFFF});
			x++;
		}
		y++;
	}
}

void	draw_player(t_cub3d *cub)
{
	draw_rectangle(cub, cub->player->x - cub->player->size / 2, \
			cub->player->y - cub->player->size / 2, \
			cub->player->size);
	cast_ray(cub);
}

/*
void	draw_player_direction(t_cub3d *cub)
{
	t_player	*p;
	t_ray		*r;
	t_pixel		start;
	t_pixel 	end;

	p = cub->player;
	r = cub->ray;
	printf("Angle ray: [%f] PLayer angle: [%f]\n", cub->ray->rangle, cub->player->rangle);
	start = init_pixel(p->x, p->y, RED);
	end = init_pixel(p->x + cos(r->rangle) * 50, \
					p->y + sin(r->rangle) * 50, 
					RED);
	draw_line(cub, init_line(start, end));
}
*/
