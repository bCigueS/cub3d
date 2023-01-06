/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:05:28 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/06 10:37:59 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_a_wall(t_cub3d *cub, double x, double y)
{
	int	mx;
	int	my;

	if ((x < 0 || x > WINDOW_WIDTH) || (y < 0 || y > WINDOW_HEIGHT))
		return (false);
	mx = floor(x / TILE_SIZE);
	my = floor(y / TILE_SIZE);
	if (cub->map[my][mx] == 1)
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

double	line_len(t_player *p, double x, double y)
{
	double	distance;

	distance = (x - p->x) * (x - p->x) + (y - p->y) * (y - p->y);
	distance = floor(sqrt(distance));
	return (distance);
}
