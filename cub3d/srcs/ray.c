/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 10:19:20 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/20 12:07:19 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_tab(t_cub3d *cub)
{
	int		i;
	double	ray_number;
	double	angle;
	double	increment_angle;

	ray_number = WINDOW_WIDTH / STRIP;
	angle = cub->player->rangle - FOV / 2;
	increment_angle = FOV / ray_number;
	cub->tab_ray = (t_ray **)malloc(sizeof(t_ray *) * ray_number);
	if (!cub->tab_ray)
		return ;
	i = 0;
	while (i < ray_number)
	{
		cub->tab_ray[i] = init_ray(angle);
		angle += increment_angle;
		i++;
	}
}

t_ray	*init_ray(double angle)
{
	t_ray		*r;

	r = (t_ray *)malloc(sizeof(t_ray));
	if (!r)
		return (NULL);
	r->rangle = angle;
	if (r->rangle > 0 && r->rangle < M_PI)
		r->ray_down = true;
	else
		r->ray_down = false;
	if (r->rangle < 0.5 * M_PI || r->rangle > 1.5 * M_PI)
		r->ray_left = false;
	else
		r->ray_left = true;
	return (r);
}

void	update_ray(t_cub3d *cub)
{
	int			i;
	t_ray		*r;

	i = 0;
	while (i < WINDOW_WIDTH / STRIP)
	{
		r = cub->tab_ray[i++];
		r->rangle += cub->player->turn * cub->player->rspeed;
		r->rangle = normalise_angle2(r->rangle);
		if (r->rangle > 0 && r->rangle < M_PI)
			r->ray_down = true;
		else
			r->ray_down = false;
		if (r->rangle < 0.5 * M_PI || r->rangle > 1.5 * M_PI)
			r->ray_left = false;
		else
			r->ray_left = true;
	}
}

void	draw_rays(t_cub3d *cub)
{
	int		i;
	double	ray_number;

	ray_number = WINDOW_WIDTH / STRIP;
	i = 0;
	while (i < ray_number)
		draw_ray(cub, cub->tab_ray[i++]);
	raycasting(cub);
}
