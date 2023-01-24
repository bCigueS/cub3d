/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:07:59 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/24 11:25:40 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(void *param)
{
	static int i;
	t_cub3d	*cub;

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

void	init_map(t_cub3d *cub)
{
	cub->info.map_col = 15;
	cub->info.map_row = 15;
	cub->info.map_dim_w = cub->info.map_col * TILE_SIZE;
	cub->info.map_dim_h = cub->info.map_row * TILE_SIZE;
	cub->info.player_orientation = M_PI * 1.5;
	cub->info.fov = degree_to_radian(FOV);
}	

void	init_parsing(t_parser *parser, char *argv)
{
	int	i;

	i = 0;
	parser->path_file = argv;
	parser->map.check_o = false;
	parser->map.orientation = '0';
	while (i <= C)
	{
		parser->textures[i].check = false;
		parser->textures[i].img = NULL;
		parser->textures[i].path = NULL;
		parser->textures[i].hexa_color = 0;
		i++;
	}
	parser->mlx = mlx_init();
	if (!parser->mlx)
	{
		ft_printf_fd(STDERR_FILENO, "Error\nMlx init failed.\n");
		exit(1);
	}
}
void	convert_map_to_int(t_parser *parser, t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	cub->map = (int **)malloc(sizeof(int *) * parser->map.map_height);
	if (!cub->map)
		return ;
	while (i < parser->map.map_height)
	{
		j = 0;
		cub->map[i] = (int *)malloc(sizeof(int) * parser->map.map_widht);
		if (cub->map[i] == NULL)
			return (clean_mlx(cub));
		while (parser->map.map[i][j])
		{
			if (parser->map.map[i][j] == '1')
				cub->map[i][j] = 1;
			else if (parser->map.map[i][j] == '0')
				cub->map[i][j] = 0;
			else if (parser->map.map[i][j] == 'N' || \
						parser->map.map[i][j] == 'S' || \
						parser->map.map[i][j] == 'E' || \
						parser->map.map[i][j] == 'W')
				cub->map[i][j] = 80;
			else 
				cub->map[i][j] = 3;
			j++;
		}
		i++;
	}
}

void	bridge(t_parser *parser, t_cub3d *cub)
{
	convert_map_to_int(parser, cub);
	/*
	*/
	for (int i = 0; i < parser->map.map_height; i++) {
		for (int j = 0; j < parser->map.map_widht; j++) {
			ft_printf_fd(1, "[%d] ", cub->map[i][j]);
		}
		ft_printf_fd(1, "\n");
	}
	cub->info.map_col = parser->map.map_widht - 1;
	cub->info.map_row = parser->map.map_height - 1;
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
	
}

int	main(int argc, char **argv)
{
	t_cub3d		cub;
	t_parser	parser;
	int			i;
	if (argc != 2)
	{
		ft_printf_fd(STDERR_FILENO, "%s", USAGE);
		return (false);
	}

	init_parsing(&parser, argv[1]);
	if (parsing(&parser) == false)
		return (-1);
	else
	{
		i = 0;
		free_map(parser.tex_lines);
		while (i < 4)
			printf("Mlx img : %p\n", parser.textures[i++].img);
		while (i < 6)
			printf("Colors : 0x%x\n", parser.textures[i++].hexa_color);
		printf("\n\n");
		print_map(parser.map.map);
	}
	bridge(&parser, &cub);
	free_map(parser.map.map);
	cub3d(&cub);
	return (0);
}
