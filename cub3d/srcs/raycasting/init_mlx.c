/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:04:07 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/24 14:00:36 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	init_mini_map(t_cub3d *cub)
{
	cub->mmap.ratio = get_minimap_ratio(cub);
	cub->mmap.img = mlx_new_image(cub->mlx_ptr, \
			cub->info.map_dim_w * cub->mmap.ratio, \
			cub->info.map_dim_h * cub->mmap.ratio);
	if (cub->mmap.img == NULL)
		return (clean_mlx(cub), false);
	cub->mmap.addr = (int *)mlx_get_data_addr(cub->mmap.img, \
			&cub->mmap.bpp, \
			&cub->mmap.line_len, \
			&cub->mmap.endian);
	if (cub->mmap.addr == NULL)
		return (clean_mlx(cub), false);
	return (true);
}

static bool	init_img(t_cub3d *cub)
{
	cub->img.ratio = 1;
	cub->img.img = mlx_new_image(cub->mlx_ptr, \
			WINDOW_WIDTH, \
			WINDOW_HEIGHT);
	if (cub->img.img == NULL)
		return (clean_mlx(cub), false);
	cub->img.addr = (int *)mlx_get_data_addr(cub->img.img, \
			&cub->img.bpp, \
			&cub->img.line_len, \
			&cub->img.endian);
	if (cub->img.addr == NULL)
		return (clean_mlx(cub), false);
	return (true);
}

static void	init_texture(t_cub3d *cub)
{
	int	i;

	cub->texture[0].img.img = \
				mlx_xpm_file_to_image(cub->mlx_ptr, "./sprites/vent1.xpm", \
						&cub->texture[0].icon_w, &cub->texture[0].icon_h);
	cub->texture[1].img.img = \
				mlx_xpm_file_to_image(cub->mlx_ptr, "./sprites/wall1.xpm", \
						&cub->texture[1].icon_w, &cub->texture[1].icon_h);
	cub->texture[2].img.img = \
				mlx_xpm_file_to_image(cub->mlx_ptr, "./sprites/window.xpm", \
						&cub->texture[2].icon_w, &cub->texture[2].icon_h);
	cub->texture[3].img.img = \
				mlx_xpm_file_to_image(cub->mlx_ptr, "./sprites/crate1.xpm", \
						&cub->texture[3].icon_w, &cub->texture[3].icon_h);
	cub->texture[4].img.img = \
				mlx_xpm_file_to_image(cub->mlx_ptr, "./sprites/door1.xpm", \
						&cub->texture[4].icon_w, &cub->texture[4].icon_h);
	i = 0;
	while (i < 5)
	{
		cub->texture[i].img.addr = (int *)mlx_get_data_addr(\
				cub->texture[i].img.img, &cub->texture[i].img.bpp, \
				&cub->texture[i].img.line_len, &cub->texture[i].img.endian);
		i++;
	}
}

static void	init_textures(t_cub3d *cub)
{
	cub->texture = (t_texture *)malloc(sizeof(t_texture) * 5);
	if (!cub->texture)
		return (clean_mlx(cub));
	init_texture(cub);
}

bool	init_mlx(t_cub3d *cub)
{
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->img.img = NULL;
	cub->mmap.img = NULL;
	cub->player = NULL;
	cub->texture = NULL;
	cub->door = NULL;
	cub->tab_ray = NULL;
	cub->mlx_ptr = mlx_init();
	if (cub->mlx_ptr == NULL)
		return (false);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, \
			"cub3d");
	if (cub->win_ptr == NULL)
		return (clean_mlx(cub), false);
	if (!init_mini_map(cub))
		return (clean_mlx(cub), false);
	if (!init_img(cub))
		return (clean_mlx(cub), false);
	init_textures(cub);
	//init_door_tex(cub);
	if (cub->texture == NULL)
		return (clean_mlx(cub), false);
	return (true);
}
