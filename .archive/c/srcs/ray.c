/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 09:47:57 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/18 22:07:45 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	*create_ray(double ray_angle)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->rangle = ray_angle;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	if (ray->rangle > 0 && ray->rangle < M_PI)
		ray->ray_down = true;
	if (ray->rangle < 0.5 * M_PI || ray->rangle > 1.5 * M_PI)
		ray->ray_right = true;
	return (ray);
}

bool	init_ray(t_cub3d *cub)
{
	int	i;
	double ray_angle;
	double ray_number = WINDOW_WIDTH / WALL_STRIP_WIDTH;

	i = 0;
	ray_angle = cub->player->rangle - (FOV / 2);
	cub->ray = (t_ray **)malloc(sizeof(t_ray *) * RAY_NUMBER);
	if (!cub->ray)
		return (false);
	while (i < RAY_NUMBER)
	{
		cub->ray[i] = create_ray(ray_angle);
		if (!cub->ray[i])
			return (false);
		ray_angle += (FOV / ray_number);
		i++;
	}
	return (true);
}

void	cast_ray(t_cub3d *cub)
{
	int i;
	t_pixel	start;
	t_pixel	end;

	i = 0;
	while (i < RAY_NUMBER)
	{
		start = init_pixel(cub->player->x, cub->player->y, RED);
		end = init_pixel(cub->player->x + cos(cub->ray[i]->rangle) * 30, \
				cub->player->y + sin(cub->ray[i]->rangle) * 30, \
				RED);
		draw_line(cub, init_line(start, end));
		i++;
	}
}

void	update_ray(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < RAY_NUMBER)
	{
		cub->ray[i]->rangle += cub->player->turn * cub->player->rspeed;	
		i++;
	}
}

void	cast_ray(t_cub3d *cub)
{
	int	xstep;
	int	ystep;
	int	xintercept;
	int	yintercept;

	yintercept = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	if (cub->ray->ray_down)
		yintercept += TILE_SIZE;
	xintercept = cub->player->x + ((yintercept - cub->player->y) / tan(cub->ray->rangle));
	ystep = TILE_SIZE;
	if (!cub->ray->ray_down)
		ystep *= -1;
	xstep = TILE_SIZE / tan(cub->ray->rangle);
	if (!cub->ray->ray_right && xstep > 0)
		xstep *= -1;
	if (cub->ray->ray_right && xstep < 0)
		xstep *= -1;


	int next_horizontal_touch_x = xintercept;
	int next_horizontal_touch_y = yintercept;
	<F4>
	
	if (!cub->ray->ray_down)
		next_horizontal_touch_y--;
	while () {
		if (is_not_wall(cub->map,next_horizontal_touch_x, next_horizontal_touch_y) == true) {
			break ;
		}
		else {
			next_horizontal_touch_x += xstep;
			next_horizontal_touch_y += ystep;
		}
	}
}
