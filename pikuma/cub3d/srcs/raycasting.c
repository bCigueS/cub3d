/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:37:34 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/06 10:09:21 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	choose_color(t_ray *r, t_pixel *start, t_pixel *end)
{
	unsigned int color;

	if (r->is_horizontal_hit && r->ray_down)
		color = RED;
	else if (r->is_horizontal_hit && !r->ray_down)
		color = GREEN;
	else if (!r->is_horizontal_hit && r->ray_left)
		color = BLUE;
	else if (!r->is_horizontal_hit && !r->ray_left)
		color = GOLD;
	else 
		color = BLACK;

	start->color = color;
	end->color = color;
}

static void	raycasting_draw_wall(t_cub3d *cub, t_rcinfo rci, t_ray *r, int *pi)
{
	int		next;
	t_pixel	start;
	t_pixel	end;

	next = *pi + STRIP;
	choose_color(r, &start, &end);
	while (*pi < next)
	{
		start = init_pixel(*pi, WINDOW_HEIGHT / 2 - (rci.wall_height / 2), \
				start.color);
		end = init_pixel(*pi, WINDOW_HEIGHT / 2 + (rci.wall_height / 2), \
				end.color);
		draw_line(cub->img, init_line(start, end));
		*pi += 1;
	}
}

static void	init_rcinfo(t_rcinfo *rci)
{
	rci->fov = FOV / 2;
	rci->halfwindow = WINDOW_WIDTH / 2;
	rci->wall_projection_distance = rci->halfwindow / tan(rci->fov);
}

void	raycasting(t_cub3d *cub)
{
	int			i;
	int			pixel_index;
	t_rcinfo	rayc;
	t_ray		*r;

	i = 0;
	pixel_index = 0;
	init_rcinfo(&rayc);
	while (i < WINDOW_WIDTH / STRIP)
	{
		r = cub->tab_ray[i++];
		rayc.correct_distance = cos(r->rangle - cub->player->rangle) * \
							r->distance;
		rayc.wall_height = (TILE_SIZE / rayc.correct_distance) * \
							rayc.wall_projection_distance;
		raycasting_draw_wall(cub, rayc, r, &pixel_index);
	}
}
