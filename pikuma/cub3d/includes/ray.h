/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 10:16:50 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/02 17:47:46 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct	s_ray
{
	double		rangle;
	bool		ray_down;
	bool		ray_left;
	int			xwallh;
	int			xwallv;
	int			ywallh;
	int			ywallv;
}				t_ray;

t_ray	*init_ray(t_cub3d *cub);
void	draw_ray(t_cub3d *cub);
void	update_ray(t_cub3d *cub);
bool	update_ray2(t_cub3d *cub);
bool	update_ray3(t_cub3d *cub);

#endif
