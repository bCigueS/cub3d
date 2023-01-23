/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:35:38 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/23 10:53:34 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (0);
}
