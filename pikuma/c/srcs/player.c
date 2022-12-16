/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:55:15 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/16 16:21:09 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_player	*create_player(int x, int y)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->x = x * (TILE_SIZE / 2);
	player->y = y * (TILE_SIZE / 2);
	player->mspeed = 4;
	player->rspeed = 4;
	player->size = 10;
	player->rangle = M_PI;
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
			
