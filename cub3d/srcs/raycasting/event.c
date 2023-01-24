/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:35:38 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/23 17:02:25 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_next_to_door(t_cub3d *cub)
{
	int	x;
	int	y;
	int	**map;
	double a;

	x = floor(cub->player->x / TILE_SIZE);
	y = floor(cub->player->y / TILE_SIZE);
	map = cub->map;
	a = cub->player->rangle;

	if ((map[y - 1][x] == 68 || map[y - 1][x] == 2) && (a > 1.25 * M_PI && a < 1.75 * M_PI))
		return (map[y - 1][x]);
	if ((map[y + 1][x] == 68 || map[y + 1][x] == 2) && (a > 0.25 * M_PI && a < 0.75 * M_PI))
		return (map[y + 1][x]);
	if ((map[y][x + 1] == 68 || map[y][x + 1] == 2) && (a > 1.75 * M_PI || a < 0.25 * M_PI))
	{
		ft_printf("Ya une porte\n");
		return (map[y][x + 1]);
	}
	if ((map[y][x - 1] == 68 || map[y][x - 1] == 2) && (a > 0.75 * M_PI && a < 1.25 * M_PI))
		return (map[y][x - 1]);
	return (0);
}

void	action_open(t_cub3d *cub)
{
	int	x;
	int	y;
	int	**map;
	double a;

	x = floor(cub->player->x / TILE_SIZE);
	y = floor(cub->player->y / TILE_SIZE);
	map = cub->map;
	a = cub->player->rangle;
	if ((map[y - 1][x] == 68) && (a > 1.25 * M_PI && a < 1.75 * M_PI))
		map[y - 1][x] = 2;
	else if ((map[y + 1][x] == 68) && (a > 0.25 * M_PI && a < 0.75 * M_PI))
		map[y + 1][x] = 2;
	else if ((map[y][x + 1] == 68) && (a > 1.75 * M_PI || a < 0.25 * M_PI))
		map[y][x + 1] = 2;
	else if ((map[y][x - 1] == 68) && (a > 0.75 * M_PI && a < 1.25 * M_PI))
		map[y][x - 1] = 2;
}

void	action_close(t_cub3d *cub)
{
	int	x;
	int	y;
	int	**map;
	double a;

	x = floor(cub->player->x / TILE_SIZE);
	y = floor(cub->player->y / TILE_SIZE);
	map = cub->map;
	a = cub->player->rangle;
	if ((map[y - 1][x] == 2) && (a > 1.25 * M_PI && a < 1.75 * M_PI))
		map[y - 1][x] = 68;
	else if ((map[y + 1][x] == 2) && (a > 0.25 * M_PI && a < 0.75 * M_PI))
		map[y + 1][x] = 68;
	else if ((map[y][x + 1] == 2) && (a > 1.75 * M_PI || a < 0.25 * M_PI))
		map[y][x + 1] = 68;
	else if ((map[y][x - 1] == 2) && (a > 0.75 * M_PI && a < 1.25 * M_PI))
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

static void	player_mouvement(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_W)
		cub->player->walk = 1;
	else if (keycode == KEY_S)
		cub->player->walk = -1;
	else if (keycode == KEY_ARROW_LEFT)
		cub->player->turn = -1;
	else if (keycode == KEY_ARROW_RIGHT)
		cub->player->turn = 1;
	update_player(cub);
}

static void	straf(t_player *p, t_cub3d *cub, double straf)
{
	int			i;
	double		newx;
	double		newy;

	i = p->walk;
	newx = p->x + cos(straf) * (p->mspeed + 2);
	newy = p->y + sin(straf) * (p->mspeed + 2);
	if (!(is_a_wall(cub, newx, newy)))
	{
		p->x = newx;
		p->y = newy;
		if ((int)p->x % TILE_SIZE == 0 || (int)p->y % TILE_SIZE == 0)
			p->x -= cos(straf);
	}
}

static void	player_straf(int keycode, t_cub3d *cub)
{
	t_player	*p;

	p = cub->player;
	if (keycode == KEY_D)
	{
		p->straf = p->rangle + M_PI / 2;
		straf(cub->player, cub, p->straf);
	}
	else if (keycode == KEY_A)
	{
		p->straf = p->rangle - M_PI / 2 ;
		straf(cub->player, cub, p->straf);
	}
	update_ray(cub);
	p->straf = 0;
}

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
	if (keycode == KEY_S || keycode == KEY_W || keycode == KEY_ARROW_LEFT || \
			keycode == KEY_ARROW_RIGHT)
		player_mouvement(keycode, cub);
	if (keycode == KEY_A || keycode == KEY_D)
		player_straf(keycode, cub);
	if (keycode == KEY_SPACE)
		open_close_door(cub);
	return (0);
}
