/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:05:28 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/24 12:59:01 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_a_wall(t_cub3d *cub, double x, double y)
{
	int	mx;
	int	my;

	if ((x < 0 || x > cub->info.map_dim_w) || \
			(y < 0 || y > cub->info.map_dim_h))
		return (false);
	mx = floor(x / TILE_SIZE);
	my = floor(y / TILE_SIZE);
	if (mx >= cub->info.map_col || my >= cub->info.map_row)
		return (false);
	if (cub->map[my][mx] == 1 || cub->map[my][mx] == 68)
		return (true);
	return (false);
}

void	normalise_angle(t_player *p)
{
	if (p->rangle < 0)
		p->rangle = 2 * M_PI + p->rangle;
	else if (p->rangle >= 2 * M_PI)
		p->rangle = p->rangle - M_PI * 2;
}

double	normalise_angle2(double angle)
{
	double	norm_angle;

	norm_angle = angle;
	if (angle < 0)
		norm_angle = 2 * M_PI + angle;
	else if (angle >= 2 * M_PI)
		norm_angle = angle - M_PI * 2;
	return (norm_angle);
}

double	line_len(t_player *p, double x, double y)
{
	double	distance;

	distance = (x - p->x) * (x - p->x) + (y - p->y) * (y - p->y);
	distance = sqrt(distance);
	return (distance);
}

double	degree_to_radian(double angle)
{
	return (angle * (M_PI / 180));
}
