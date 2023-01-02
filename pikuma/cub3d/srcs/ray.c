/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 10:19:20 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/02 17:47:48 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	*init_ray(t_cub3d *cub)
{
	t_player	*p;
	t_ray		*r;

	p = cub->player;
	r = (t_ray *)malloc(sizeof(t_ray));
	if (!r)
		return (NULL);
	r->rangle = p->rangle;
	if (r->rangle > 0 && r->rangle <= M_PI)
		r->ray_down = true;
	if (r->rangle <= (M_PI + M_PI / 2) && r->rangle >= M_PI / 2)
		r->ray_left = true;
	return (r);
}

void	update_ray(t_cub3d *cub)
{
	t_player	*p;
	t_ray		*r;

	p = cub->player;
	r = cub->ray;
	r->rangle = p->rangle;
	if (r->rangle > 0 && r->rangle < M_PI)
		r->ray_down = true;
	else
		r->ray_down = false;
	if (r->rangle > 0.5 * M_PI  && r->rangle < 1.5 * M_PI)
		r->ray_left = true;
	else
		r->ray_left = false;
}

bool	update_ray2(t_cub3d *cub)
{
	t_player 	*p;
	t_ray		*r;
	int			xstep;
	int			ystep;
	int			xintercept;
	int			yintercept;

	p = cub->player;
	r = cub->ray;
	yintercept = floor(p->y / TILE_SIZE) * TILE_SIZE;
	if (r->ray_down)
		yintercept += TILE_SIZE;
	xintercept = p->x + (yintercept - p->y) / tan(r->rangle);
	ystep = TILE_SIZE;
	if (!r->ray_down)
		ystep *= -1;
	xstep = TILE_SIZE / tan(r->rangle);
	if (r->ray_left && xstep > 0)
		xstep *= -1;
	if (!r->ray_left && xstep < 0)
		xstep *= -1;

	int	nextx = xintercept;
	int	nexty = yintercept;

	if (!r->ray_down)
		nexty--;
	while (nextx >= 0 && nextx <= WINDOW_WIDTH && nexty >= 0 && nexty <= WINDOW_HEIGHT)
	{
		if (is_a_wall(cub, nextx, nexty)) {
			if (!r->ray_down)
				nexty++;
			r->xwallh = nextx;
			r->ywallh = nexty;
			return (true);
		}
		else {
			nextx += xstep;
			nexty += ystep;
		}
	}
	return (false);
}

bool	update_ray3(t_cub3d *cub)
{
	t_player 	*p;
	t_ray		*r;
	int			xstep;
	int			ystep;
	int			xintercept;
	int			yintercept;

	p = cub->player;
	r = cub->ray;
	xintercept = floor(p->x / TILE_SIZE) * TILE_SIZE;
	if (!r->ray_left)
		xintercept += TILE_SIZE;
	yintercept = p->y + (xintercept - p->x) * tan(r->rangle);
	xstep = TILE_SIZE;
	if (r->ray_left)
		xstep *= -1;
	ystep = TILE_SIZE * tan(r->rangle);
	if (!r->ray_down && ystep > 0)
		ystep *= -1;
	if (r->ray_down && ystep < 0)
		ystep *= -1;

	int	nextx = xintercept;
	int	nexty = yintercept;

	if (r->ray_left)
		nextx--;
	while (nextx >= 0 && nextx <= WINDOW_WIDTH && nexty >= 0 && nexty <= WINDOW_HEIGHT)
	{
		if (is_a_wall(cub, nextx, nexty)) {
			nextx--;
			//draw_line(cub, init_line(init_pixel(p->x, p->y, RED), init_pixel(nextx, nexty, RED)));
			r->xwallv = nextx;
			r->ywallv = nexty;
			return (true);
		}
		else {
			nextx += xstep;
			nexty += ystep;
		}
	}
	return (false);
}

int		line_len(t_player *p, int x, int y)
{
	int distance;

	distance = (x - p->x) * (x - p->x) + (y - p->y) * (y - p->y);
	distance = floor(sqrt(distance));
	return (distance);
}

void	draw_ray(t_cub3d *cub)
{
	unsigned int	color = RED;
	int				x = cub->player->x;
	int				y = cub->player->y;
	int				endx;
	int				endy;
	int				horizontalHit;
	int				verticalHit;

	if (update_ray2(cub))
		horizontalHit = line_len(cub->player, cub->ray->xwallh, cub->ray->ywallh);
	else
		horizontalHit = 100000000;
	if (update_ray3(cub))
		verticalHit = line_len(cub->player, cub->ray->xwallv, cub->ray->ywallv);
	else
		verticalHit = 100000000;
	if (horizontalHit < verticalHit) {
		endx = cub->ray->xwallh;
		endy = cub->ray->ywallh;
	}
	else {
		endx = cub->ray->xwallv;
		endy = cub->ray->ywallv;
	}





	
	draw_line(cub, init_line(init_pixel(x, y, color), \
				init_pixel(endx, endy, color)));
}
