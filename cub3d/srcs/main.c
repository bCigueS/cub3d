/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:07:59 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/23 12:34:39 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	mlx_clear_window(cub->mlx_ptr, cub->win_ptr);
	draw_ceiling_floor(cub);
	draw_background(cub);
	draw_map(cub);
	draw_player(cub);
	draw_rays(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img, 0, 0);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->mmap.img, 10, 10);
	return (0);
}

bool	cub3d(t_cub3d *cub)
{
	if (init_mlx(cub) == false)
		return (clean_mlx(cub), false);
	cub->player = init_player(cub);
	if (cub->player == NULL)
		return (clean_mlx(cub), false);
	init_ray_tab(cub);
	if (cub->tab_ray == NULL)
		return (false);
	mlx_hook(cub->win_ptr, EXIT, 0, &quit, cub);
	mlx_hook(cub->win_ptr, KEY_PRESS, (1L << 0), handle_key, cub);
	mlx_loop_hook(cub->mlx_ptr, render, cub);
	mlx_loop(cub->mlx_ptr);
	return (true);
}

int	**create_map(int imap[15][15], int xx, int yy)
{
	int		**map;
	int		x;
	int		y;

	map = (int **)malloc(sizeof(int *) * yy);
	if (!map)
		return (NULL);
	y = 0;
	while (y < yy)
	{
		x = 0;
		map[y] = (int *)malloc(sizeof(int) * xx);
		if (!map[y])
			return (NULL);
		while (x < xx)
		{
			map[y][x] = imap[y][x];
			x++;
		}
		y++;
	}
	return (map);
}

void	init_map(t_cub3d *cub)
{
	cub->info.map_col = 15;
	cub->info.map_row = 15;
	cub->info.map_dim_w = cub->info.map_col * TILE_SIZE;
	cub->info.map_dim_h = cub->info.map_row * TILE_SIZE;
	cub->info.player_orientation = M_PI * 1.5;
	cub->info.fov = degree_to_radian(FOV);
}	

int	main(void)
{
	t_cub3d	cub;
	int		map[MH][MW] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 80, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	/*
	int		map[MH][MW] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	*/

	/*
	int		map2[3][15] = {\
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },\
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },\
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }};
	*/
	cub.map = create_map(map, 15, 15);
	init_map(&cub);
	cub3d(&cub);
	return (0);
}
