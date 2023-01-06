/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 09:44:23 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/18 20:16:24 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct s_cub3d t_cub3d;

typedef struct	s_ray
{
	double 		rangle;
	int			wall_hit_x;
	int			wall_hit_y;
	bool		ray_down;
	bool		ray_right;
}				t_ray;

bool	init_ray(t_cub3d *cub);
t_ray	*create_ray(double ray_angle);
void	update_ray(t_cub3d *cub);
void	cast_ray(t_cub3d *cub);

#endif
