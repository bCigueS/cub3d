/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:08:46 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/24 14:01:05 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(void *param)
{
	static int	i;
	t_cub3d		*cub;

	cub = (t_cub3d *)param;
	cub->door_to_show = &cub->door[i % 5];
	i++;
	if (i == 25)
		i = 0;
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

static void	fill_map(t_parser *parser, t_cub3d *cub, int x, int y)
{
	if (parser->map.map[y][x] == '1')
		cub->map[y][x] = 1;
	else if (parser->map.map[y][x] == '0')
		cub->map[y][x] = 0;
	else if (parser->map.map[y][x] == 'N' || \
			parser->map.map[y][x] == 'S' || \
			parser->map.map[y][x] == 'E' || \
			parser->map.map[y][x] == 'W')
		cub->map[y][x] = 80;
	else
		cub->map[y][x] = 3;
}

static void	convert_map_to_int(t_parser *parser, t_cub3d *cub)
{
	int	y;
	int	x;

	y = -1;
	cub->map = (int **)malloc(sizeof(int *) * parser->map.map_height);
	if (!cub->map)
		return ;
	while (++y < parser->map.map_height)
	{
		x = -1;
		cub->map[y] = (int *)malloc(sizeof(int) * (parser->map.map_widht - 1));
		if (cub->map[y] == NULL)
			return (clean_mlx(cub));
		while (++x < parser->map.map_widht - 1)
			fill_map(parser, cub, x, y);
	}
}

static void	bridge(t_parser *parser, t_cub3d *cub)
{
	convert_map_to_int(parser, cub);
	cub->info.map_col = parser->map.map_widht - 1;
	cub->info.map_row = parser->map.map_height;
	ft_printf_fd(1, "Col:[%d]\tRow:[%d]\n", cub->info.map_col, cub->info.map_row);
	cub->info.map_dim_w = cub->info.map_col * TILE_SIZE;
	cub->info.map_dim_h = cub->info.map_row * TILE_SIZE;
	if (parser->map.orientation == 'N')
		cub->info.player_orientation = M_PI * 1.5;
	else if (parser->map.orientation == 'S')
		cub->info.player_orientation = M_PI * 0.5;
	else if (parser->map.orientation == 'E')
		cub->info.player_orientation = M_PI;
	else
		cub->info.player_orientation = 0;
	cub->info.fov = degree_to_radian(FOV);
	cub->info.ceilling = parser->textures[4].hexa_color;
	cub->info.floor = parser->textures[5].hexa_color;
}

bool	cub3d(t_cub3d *cub, t_parser *parser)
{
	bridge(parser, cub);
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
