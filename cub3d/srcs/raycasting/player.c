/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 07:32:38 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/24 15:42:38 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	player_get_position(t_cub3d *cub, t_player **player)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->info.map_row)
	{
		x = 0;
		while (x < cub->info.map_col)
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

static void	update_player_walk(t_cub3d *cub, t_player *p, int move, int i)
{
	double	newx;
	double	newy;

	while (abs(i) <= abs(move))
	{
		newx = p->x + cos(p->rangle) * i;
		newy = p->y + sin(p->rangle) * i;
		if (!is_a_wall(cub, newx, newy))
		{
			if (p->walk == -1)
				i--;
			else
				i++;
			p->x = newx;
			p->y = newy;
			if (i == move)
				break ;
		}
		else
		{
			player_stepback(p);
			break ;
		}
	}
}

void	draw_player(t_cub3d *cub)
{
	int				x;
	int				y;
	unsigned int	color;
	double			ratio;

	y = 0;
	ratio = cub->mmap.ratio;
	while (y < cub->player->icon_h)
	{
		x = 0;
		while (x < cub->player->icon_w)
		{
			color = cub->player->img.addr[x + cub->player->icon_w * y];
			if (color != 0xFF000000)
				draw_pixel(cub, \
						(t_pixel){(x + cub->player->x - (15 / 2)) * ratio, \
						(y + cub->player->y - (15 / 2)) * ratio, RED}, \
						MINI_MAP);
			x++;
		}
		y++;
	}
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
	player->straf = 0;
	player->rangle = cub->info.player_orientation;
	player->rspeed = 4 * (M_PI / 180);
	if (player_get_position(cub, &player) == false)
		return (free(player), NULL);
	player->img.img = mlx_xpm_file_to_image(cub->mlx_ptr, \
			"./sprites/cercle.xpm", &player->icon_w, &player->icon_h);
	if (!player->img.img)
		return (free(player), NULL);
	player->img.addr = (int *)mlx_get_data_addr(player->img.img, \
			&player->img.bpp, &player->img.line_len, &player->img.endian);
	if (cub->img.addr == NULL)
		return (free(player->img.img), free(player), NULL);
	return (player);
}

void	update_player(t_cub3d *cub)
{
	t_player	*p;
	int			move;

	p = cub->player;
	p->rangle += p->turn * p->rspeed;
	normalise_angle(p);
	move = p->walk * p->mspeed;
	update_player_walk(cub, p, move, p->walk);
	update_ray(cub);
	p->walk = 0;
	p->turn = 0;
}
