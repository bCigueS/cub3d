/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:30:47 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/24 13:45:16 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	p_look(double angle)
{
	if (angle > 1.25 * M_PI && angle < 1.75)
		return (LOOK_UP);
	else if (angle > 0.25 && angle < 0.75)
		return (LOOK_DOWN);
	else if (angle > 1.75 || angle < 0.25)
		return (LOOK_RIGHT);
	else
		return (LOOK_LEFT);
}

static int	player_next_to_door(t_cub3d *cub)
{
	int		x;
	int		y;
	int		**map;
	double	a;

	x = floor(cub->player->x / TILE_SIZE);
	y = floor(cub->player->y / TILE_SIZE);
	map = cub->map;
	a = cub->player->rangle;
	if ((map[y - 1][x] == 68 || map[y - 1][x] == 2) && p_look(a) == LOOK_UP)
		return (map[y - 1][x]);
	if ((map[y + 1][x] == 68 || map[y + 1][x] == 2) && p_look(a) == LOOK_DOWN)
		return (map[y + 1][x]);
	if ((map[y][x + 1] == 68 || map[y][x + 1] == 2) && p_look(a) == LOOK_RIGHT)
	{
		ft_printf("Ya une porte\n");
		return (map[y][x + 1]);
	}
	if ((map[y][x - 1] == 68 || map[y][x - 1] == 2) && p_look(a) == LOOK_LEFT)
		return (map[y][x - 1]);
	return (0);
}

static void	action_open(t_cub3d *cub)
{
	int		x;
	int		y;
	int		**map;
	double	a;

	x = floor(cub->player->x / TILE_SIZE);
	y = floor(cub->player->y / TILE_SIZE);
	map = cub->map;
	a = cub->player->rangle;
	if ((map[y - 1][x] == 68) && p_look(a) == LOOK_UP)
		map[y - 1][x] = 2;
	else if ((map[y + 1][x] == 68) && p_look(a) == LOOK_DOWN)
		map[y + 1][x] = 2;
	else if ((map[y][x + 1] == 68) && p_look(a) == LOOK_RIGHT)
		map[y][x + 1] = 2;
	else if ((map[y][x - 1] == 68) && p_look(a) == LOOK_LEFT)
		map[y][x - 1] = 2;
}

static void	action_close(t_cub3d *cub)
{
	int		x;
	int		y;
	int		**map;
	double	a;

	x = floor(cub->player->x / TILE_SIZE);
	y = floor(cub->player->y / TILE_SIZE);
	map = cub->map;
	a = cub->player->rangle;
	if ((map[y - 1][x] == 2) && p_look(a) == LOOK_UP)
		map[y - 1][x] = 68;
	else if ((map[y + 1][x] == 2) && p_look(a) == LOOK_DOWN)
		map[y + 1][x] = 68;
	else if ((map[y][x + 1] == 2) && p_look(a) == LOOK_RIGHT)
		map[y][x + 1] = 68;
	else if ((map[y][x - 1] == 2) && p_look(a) == LOOK_LEFT)
		map[y][x - 1] = 68;
}

void	open_close_door(t_cub3d *cub)
{
	int	action;

	action = player_next_to_door(cub);
	if (action == 68)
		action_open(cub);
	else if (action == 2)
		action_close(cub);
}
