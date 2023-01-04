/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:08:11 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/04 15:43:43 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(int **map)
{
	int	y;

	y = 0;
	while (y < MH)
	{
		free(map[y]);
		y++;
	}
	free(map);
}

void	clean_rays(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < WINDOW_WIDTH / STRIP)
		free(cub->tab_ray[i++]);
	free(cub->tab_ray);
}

void	clean_mlx(t_cub3d *cub)
{
	if (cub->player != NULL)
	{
		mlx_destroy_image(cub->mlx_ptr, cub->player->img.img);
		free(cub->player);
	}
	if (cub->img.img != NULL)
		mlx_destroy_image(cub->mlx_ptr, cub->img.img);
	if (cub->mini_map.img != NULL)
		mlx_destroy_image(cub->mlx_ptr, cub->mini_map.img);
	if (cub->win_ptr != NULL)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->mlx_ptr != NULL)
		mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	free_map(cub->map);
	clean_rays(cub);
}
