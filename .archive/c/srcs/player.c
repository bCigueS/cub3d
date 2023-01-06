/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:55:15 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/18 22:07:45 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_player	*create_player(int x, int y)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->x = x * TILE_SIZE + (TILE_SIZE / 2);
	player->y = y * TILE_SIZE + (TILE_SIZE / 2);
	player->turn = 0;
	player->walk = 0;
	player->rangle = M_PI / 2;
	player->mspeed = 4;
	player->rspeed = 4 * (M_PI / 180); 
	player->size = 10;
	return (player);
}

bool	init_player(t_cub3d *cub)
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
				cub->player = create_player(x, y);
				if (!cub->player)
					return (false);
				return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

void update_player(t_cub3d *cub)
{
	t_player	*p;
	int			move;
	int			newx;
	int			newy;

	p = cub->player;
	p->rangle += p->turn * p->rspeed;
	move = p->walk * p->mspeed;
	newx = p->x + (cos(p->rangle) * move);
	newy = p->y + (sin(p->rangle) * move);
	if (is_not_wall(cub->map, newx, newy))
	{
		p->x = newx;
		p->y = newy;
	}
	update_ray(cub);
	p->walk = 0;
	p->turn = 0;
}
			
