/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:46:46 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/24 13:50:04 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_door_tex(t_cub3d *cub)
{
	int	i;

	cub->door = (t_texture *)malloc(sizeof(t_texture) * 5);
	if (!cub->door)
		return (clean_mlx(cub));
	cub->door[0].img.img = \
				mlx_xpm_file_to_image(cub->mlx_ptr, "./sprites/door1.xpm", \
						&cub->door[0].icon_w, &cub->door[0].icon_h);
	cub->door[1].img.img = \
				mlx_xpm_file_to_image(cub->mlx_ptr, "./sprites/door2.xpm", \
						&cub->door[1].icon_w, &cub->door[1].icon_h);
	cub->door[2].img.img = \
				mlx_xpm_file_to_image(cub->mlx_ptr, "./sprites/door3.xpm", \
						&cub->door[2].icon_w, &cub->door[2].icon_h);
	cub->door[3].img.img = \
				mlx_xpm_file_to_image(cub->mlx_ptr, "./sprites/door4.xpm", \
						&cub->door[3].icon_w, &cub->door[3].icon_h);
	cub->door[4].img.img = \
				mlx_xpm_file_to_image(cub->mlx_ptr, "./sprites/door5.xpm", \
						&cub->door[4].icon_w, &cub->door[4].icon_h);
	i = -1;
	while (++i < 5)
		cub->door[i].img.addr = (int *)mlx_get_data_addr(\
				cub->door[i].img.img, &cub->door[i].img.bpp, \
				&cub->door[i].img.line_len, &cub->door[i].img.endian);
}
