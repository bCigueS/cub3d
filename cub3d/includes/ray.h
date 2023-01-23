/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 10:16:50 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/23 14:05:28 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# define LEFT 0
# define DOWN 1

typedef struct s_rcinfo
{
	double		fov;
	double		halfwindow;
	double		wall_projection_distance;
	double		correct_distance;
	double		wall_height;
}				t_rcinfo;

typedef struct s_wallh
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	double	nextx;
	double	nexty;
}				t_wallh;

typedef struct s_ray
{
	double		rangle;
	bool		ray_down;
	bool		ray_left;
	double		horizontal_hit;
	double		vertical_hit;
	double		distance;
	bool		is_horizontal_hit;
	t_pixel		end;
	int			wh_index_y;
	int			wh_index_x;
}				t_ray;

/* --- ray.c --- */
void	init_ray_tab(t_cub3d *cub);
t_ray	*init_ray(double angle);
void	draw_rays(t_cub3d *cub);
void	update_ray(t_cub3d *cub);

/* --- ray_intersection.c --- */
void	draw_ray(t_cub3d *cub, t_ray *r);

/* --- ray_casting.c --- */
void	raycasting(t_cub3d *cub);

#endif
