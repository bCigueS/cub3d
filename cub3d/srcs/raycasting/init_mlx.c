/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:04:07 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/25 12:23:02 by sbeylot          ###   ########.fr       */
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

static bool	init_texture(t_cub3d *cub, t_parser *parser)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		cub->texture[i].img.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
				parser->textures[i].path, &cub->texture[i].icon_w, \
				&cub->texture[i].icon_h);
		if (cub->texture[i].img.img == NULL)
		{
			ft_printf_fd(2, "Error\n");
			return (false);
		}
	}
	i = -1;
	while (++i < 4)
	{
		cub->texture[i].img.addr = (int *)mlx_get_data_addr(\
				cub->texture[i].img.img, &cub->texture[i].img.bpp, \
				&cub->texture[i].img.line_len, &cub->texture[i].img.endian);
		if (cub->texture[i].img.addr == NULL)
			return (ft_printf_fd(2, "Error\n"), false);
	}
	return (true);
}

static bool	init_textures(t_cub3d *cub, t_parser *parser)
{
	cub->texture = (t_texture *)malloc(sizeof(t_texture) * 4);
	if (!cub->texture)
		return (false);
	if (!init_texture(cub, parser))
		return (false);
	return (true);
}

bool	init_mlx(t_cub3d *cub, t_parser *parser)
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
	cub->parser = parser;
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
	if (!init_textures(cub, parser))
		return (clean_mlx(cub), false);
	if (parser->map.door && !init_door_tex(cub))
		return (clean_mlx(cub), false);
	return (true);
}
