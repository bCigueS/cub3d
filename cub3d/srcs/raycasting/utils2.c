/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:18:27 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/24 13:52:20 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_a_void(t_cub3d *cub, int x, int y)
{
	int	mx;
	int	my;

	if ((x < 0 || x > cub->info.map_dim_w) || \
			(y < 0 || y > cub->info.map_dim_h))
		return (false);
	mx = floor(x / TILE_SIZE);
	my = floor(y / TILE_SIZE);
	if (cub->map[my][mx] == 3)
		return (true);
	return (false);
}

void	colission_index(t_ray *r)
{
	int	x;
	int	y;

	if (!r->ray_down && r->is_horizontal_hit)
	{
		y = floor((r->end.y - 1) / TILE_SIZE);
		x = floor(r->end.x / TILE_SIZE);
	}
	else if (r->ray_down && r->is_horizontal_hit)
	{
		y = floor(r->end.y / TILE_SIZE);
		x = floor(r->end.x / TILE_SIZE);
	}
	else if (r->ray_left && !r->is_horizontal_hit)
	{
		y = floor(r->end.y / TILE_SIZE);
		x = floor((r->end.x - 1) / TILE_SIZE);
	}
	else
	{
		y = floor(r->end.y / TILE_SIZE);
		x = floor(r->end.x / TILE_SIZE);
	}
	r->wh_index_y = y;
	r->wh_index_x = x;
}

double	get_minimap_ratio(t_cub3d *cub)
{
	double	ratio;

	if (cub->info.map_dim_w > cub->info.map_dim_h)
		ratio = (WINDOW_WIDTH * 30) / cub->info.map_dim_w;
	else
		ratio = (WINDOW_HEIGHT * 30) / cub->info.map_dim_h;
	return (ratio / 100);
}

void	player_stepback(t_player *p)
{
	if (p->walk == 1)
	{
		p->x = p->x - cos(p->rangle);
		p->y = p->y - sin(p->rangle);
	}
	else
	{
		p->x = p->x + cos(p->rangle);
		p->y = p->y + sin(p->rangle);
	}
}
