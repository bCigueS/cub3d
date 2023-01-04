/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:07:59 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/04 12:23:38 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	quit(void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	mlx_loop_end(cub->mlx_ptr);
	clean_mlx(cub);
	exit(0);
	return (0);
}

int	handle_key(int keycode, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	(void)cub;
	if (keycode == KEY_ESC)
		quit(param);
	if (keycode == KEY_W)
	{
		cub->player->walk = 1;
		update_player(cub);
	}
	if (keycode == KEY_S)
	{
		cub->player->walk = -1;
		update_player(cub);
	}
	if (keycode == KEY_A)
	{
		int	newx = cub->player->x - cub->player->mspeed;
		if (is_a_wall(cub, newx, cub->player->y))
			return (0);
		cub->player->x -= cub->player->mspeed;
		update_player(cub);
	}
	if (keycode == KEY_D)
	{
		int	newx = cub->player->x + cub->player->mspeed;
		if (is_a_wall(cub, newx, cub->player->y))
			return (0);
		cub->player->x += cub->player->mspeed;
		update_player(cub);
	}
	if (keycode == KEY_ARROW_LEFT)
	{
		cub->player->turn = 1;
		update_player(cub);
	}
	if (keycode == KEY_ARROW_RIGHT)
	{
		cub->player->turn = -1;
		update_player(cub);
	}

	return (0);
}

void	render(t_cub3d *cub)
{
	draw_background(cub);
	draw_map(cub);
	draw_player(cub);
	draw_rays(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img, 0, 0);
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
	mlx_hook(cub->win_ptr, KEY_PRESS, (1L<<0), &handle_key, cub);
	render(cub);
	mlx_loop(cub->mlx_ptr);
	return (true);
}

int	**create_map(int imap[MH][MW])
{
	int	**map;
	int		x;
	int		y;

	map = (int **)malloc(sizeof(int *) * MH);
	if (!map)
		return (NULL);
	y = 0;
	while (y < MH)
	{
		x = 0;
		map[y] = (int *)malloc(sizeof(int) * MW);
		if (!map[y])
			return (NULL);
		while (x < MW)
		{
			map[y][x] = imap[y][x];
			x++;
		}
		y++;
	}
	return (map);
}



int main(void)
{
	t_cub3d	cub;
	int	map[MH][MW] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
					{1, 0, 0, 0, 0, 1, 1, 80, 0, 0, 0, 0, 0, 0, 1},
					{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
					{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
					{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
					{1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
					{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	cub.map = create_map(map);
	cub3d(&cub);
	return (0);
}
