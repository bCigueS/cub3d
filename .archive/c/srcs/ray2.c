/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:58:37 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/19 14:00:07 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

bool	init_ray(t_cub3d *cub)
{
	int 	i;
	double 	ray_angle;
	double	ray_number;

	ray_number = WINDOW_WIDTH / WALL_STRIP_WIDTH;
	i = 0;
	ray_angle = cub->player->rangle - (FOV / 2);
