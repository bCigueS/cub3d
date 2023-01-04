/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 10:16:50 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/03 15:26:45 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# define LEFT 0
# define DOWN 1
typedef struct s_wallh
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	double	nextx;
	double	nexty;
}				t_wallh;

typedef struct	s_ray
{
	double		rangle;
	bool		ray_down;
	bool		ray_left;
	double		horizontal_hit;
	double		vertical_hit;
	double		distance;
}				t_ray;

void	init_ray_tab(t_cub3d *cub);
t_ray	*init_ray(double angle);
void	draw_rays(t_cub3d *cub);
void	draw_ray(t_cub3d *cub, t_ray *r);
void	update_ray(t_cub3d *cub);

void	draw_3d(t_cub3d *cub);

#endif
