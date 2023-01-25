/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:46:46 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/25 12:23:08 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_door_texture(t_cub3d *cub)
{
	if (cub->door)
	{
		if (cub->door[0].img.img)
			mlx_destroy_image(cub->mlx_ptr, cub->door[0].img.img);
		if (cub->door[1].img.img)
			mlx_destroy_image(cub->mlx_ptr, cub->door[1].img.img);
		if (cub->door[2].img.img)
			mlx_destroy_image(cub->mlx_ptr, cub->door[2].img.img);
		if (cub->door[3].img.img)
			mlx_destroy_image(cub->mlx_ptr, cub->door[3].img.img);
		if (cub->door[4].img.img)
			mlx_destroy_image(cub->mlx_ptr, cub->door[4].img.img);
		free(cub->door);
	}
}

static bool	check_tex_door(t_cub3d *cub)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (cub->door[i].img.img == NULL)
			return (ft_printf_fd(2, "Error\n"), false);
	}
	i = -1;
	while (++i < 5)
	{
		cub->door[i].img.addr = (int *)mlx_get_data_addr(\
				cub->door[i].img.img, &cub->door[i].img.bpp, \
				&cub->door[i].img.line_len, &cub->door[i].img.endian);
		if (cub->door[i].img.addr == NULL)
			return (ft_printf_fd(2, "Error\n"), false);
	}
	return (true);
}

bool	init_door_tex(t_cub3d *cub)
{
	cub->door = (t_texture *)malloc(sizeof(t_texture) * 5);
	if (!cub->door)
		return (false);
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
	if (!check_tex_door(cub))
		return (false);
	return (true);
}
