/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 07:32:38 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/31 09:10:13 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	player_get_position(t_player **player, int map[MH][MW])
{
	int	x;
	int	y;

	y = 0;
	while (y < MH)
	{
		x = 0;
		while (x < MW)
		{
			if (map[y][x] == 80)
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
				draw_pixel(cub, (t_pixel){x + cub->player->x, y + cub->player->y, RED});
			x++;
		}
		y++;
	}
}

t_player	*init_player(t_cub3d *cub, int map[MH][MW])
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->mspeed = 4;
	player->turn = 0;
	player->walk = 0;
	player->rangle = M_PI / 2;
	player->rspeed = 4 (M_PI / 180);
	if (player_get_position(&player, map) == false)
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

