/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:04:07 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/04 16:06:29 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	init_mini_map(t_cub3d *cub)
{
	cub->mini_map.ratio = 0.3;
	cub->mini_map.img = mlx_new_image(cub->mlx_ptr, \
			WINDOW_WIDTH * cub->mini_map.ratio, \
			WINDOW_HEIGHT * cub->mini_map.ratio);
	if (cub->mini_map.img == NULL)
		return (clean_mlx(cub), false);
	cub->mini_map.addr = (int *)mlx_get_data_addr(cub->mini_map.img, \
			&cub->mini_map.bpp, \
			&cub->mini_map.line_len, \
			&cub->mini_map.endian);
	if (cub->mini_map.addr == NULL)
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

bool	init_mlx(t_cub3d *cub)
{
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->img.img = NULL;
	cub->mini_map.img = NULL;
	cub->player = NULL;
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
	return (true);
}
