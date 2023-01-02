/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 07:32:38 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/02 17:47:44 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	player_get_position(t_cub3d *cub, t_player **player)
{
	int	x;
	int	y;

	y = 0;
	while (y < MH)
	{
		x = 0;
		while (x < MW)
		{
			if (cub->map[y][x] == 80)
			{
				(*player)->x = x * TILE_SIZE + (TILE_SIZE / 2);
				(*player)->y = y * TILE_SIZE + (TILE_SIZE / 2);
				return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

void	draw_player(t_cub3d *cub)
{
	int x;
	int y;
	unsigned int color;

	y = 0;
	while (y < cub->player->icon_h)
	{
		x = 0;
		while (x < cub->player->icon_w)
		{
			color = cub->player->img.addr[x + cub->player->icon_w * y];
			if (color != 0xFF000000)
				draw_pixel(cub, (t_pixel){x + cub->player->x - (15 / 2), y + cub->player->y - (15 / 2), RED});
			x++;
		}
		y++;
	}
	cub->ray = init_ray(cub);
	update_ray2(cub);
	update_ray3(cub);
	draw_ray(cub);
	//while (!update_ray2(cub) && !update_ray3(cub));
}

t_player	*init_player(t_cub3d *cub)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->mspeed = 4;
	player->turn = 0;
	player->walk = 0;
	player->rangle = M_PI / 2;
	player->rspeed = 4 * (M_PI / 180);
	if (player_get_position(cub, &player) == false)
		return (free(player), NULL);
	player->img.img = mlx_xpm_file_to_image(cub->mlx_ptr, "./sprites/cercle.xpm", \
			&player->icon_w, &player->icon_h);
	if (!player->img.img)
		return (free(player), NULL);
	player->img.addr = (int *)mlx_get_data_addr(player->img.img, &player->img.bpp, &player->img.line_len, \
			&player->img.endian);
	if (cub->img.addr == NULL)
		return (free(player->img.img), free(player), NULL);
	return (player);
}

/*
 * Faire une fonction pour calculer le reste de distance a faire pour toucher le mur et conserver la vitess a 4 du joueur
 */
bool	is_a_wall(t_cub3d *cub, int x, int y)
{
	int	mx;
	int	my;

	if ((x < 0 || x >= WINDOW_WIDTH) || (y < 0 || y >= WINDOW_HEIGHT))
		return (false);
	mx = x / TILE_SIZE;
	my = y / TILE_SIZE;
	if (cub->map[my][mx] == 1)
		return (true);
	return (false);
}

void	update_player(t_cub3d *cub)
{
	t_player	*p;
	int			move;
	double		newx;
	double		newy;

	p = cub->player;
	p->rangle += p->turn * p->rspeed;
	/* Faire une fonction pour normalise l'angle */
	if (p->rangle < 0)
		p->rangle = 2 * M_PI + p->rangle;
	else if (p->rangle >= 2 * M_PI) 
		p->rangle = p->rangle - M_PI * 2;
	move = p->walk * p->mspeed;
	newx = p->x + cos(p->rangle) * move;
	newy = p->y + sin(p->rangle) * move;
	printf("newx:[%f]\tnewy[%f]\n", newx, newy);
	if (!is_a_wall(cub, newx, newy))
	{
		p->x = newx;
		p->y = newy;
	}
	p->walk = 0;
	p->turn = 0;
	update_ray(cub);
	render(cub);
}
