/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:22:19 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/06 10:56:23 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	wall_found(t_cub3d *cub, t_wallh *wh, t_ray *r, int direction)
{
	wh->nextx = wh->xintercept;
	wh->nexty = wh->yintercept;
	while (wh->nextx >= 0 && wh->nextx <= WINDOW_WIDTH && wh->nexty >= 0 && \
			wh->nexty <= WINDOW_HEIGHT)
	{
		if (direction == DOWN && !r->ray_down)
			wh->nexty--;
		else if (direction == LEFT && r->ray_left)
			wh->nextx--;
		if (is_a_wall(cub, wh->nextx, wh->nexty))
			return (true);
		else
		{
			if (direction == DOWN && !r->ray_down)
				wh->nexty++;
			else if (direction == LEFT && r->ray_left)
				wh->nextx++;
			wh->nextx += wh->xstep;
			wh->nexty += wh->ystep;
		}
	}
	return (false);
}

static bool	horizontal_hit(t_cub3d *cub, t_ray *r, t_wallh *wh)
{
	wh->yintercept = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	if (r->ray_down)
		wh->yintercept += TILE_SIZE;
	wh->xintercept = cub->player->x + (wh->yintercept - cub->player->y) / \
			tan(r->rangle);
	wh->ystep = TILE_SIZE;
	if (!r->ray_down)
		wh->ystep *= -1;
	wh->xstep = TILE_SIZE / tan(r->rangle);
	if (r->ray_left && wh->xstep > 0)
		wh->xstep *= -1;
	if (!r->ray_left && wh->xstep < 0)
		wh->xstep *= -1;
	return (wall_found(cub, wh, r, DOWN));
}

static bool	vertical_hit(t_cub3d *cub, t_ray *r, t_wallh *wh)
{
	wh->xintercept = floor(cub->player->x / TILE_SIZE) * TILE_SIZE;
	if (!r->ray_left)
		wh->xintercept += TILE_SIZE;
	wh->yintercept = cub->player->y + (wh->xintercept - cub->player->x) * \
			tan(r->rangle);
	wh->xstep = TILE_SIZE;
	if (r->ray_left)
		wh->xstep *= -1;
	wh->ystep = TILE_SIZE * tan(r->rangle);
	if (!r->ray_down && wh->ystep > 0)
		wh->ystep *= -1;
	if (r->ray_down && wh->ystep < 0)
		wh->ystep *= -1;
	return (wall_found(cub, wh, r, LEFT));
}

static t_pixel	assign_hit(t_cub3d *cub, t_ray *r, t_wallh *hwh, t_wallh *vwh)
{
	t_pixel	end;

	if (horizontal_hit(cub, r, hwh))
		r->horizontal_hit = line_len(cub->player, hwh->nextx, hwh->nexty);
	else
		r->horizontal_hit = 100000000;
	if (vertical_hit(cub, r, vwh))
		r->vertical_hit = line_len(cub->player, vwh->nextx, vwh->nexty);
	else
		r->vertical_hit = 100000000;
	if (r->horizontal_hit < r->vertical_hit)
	{
		end.x = hwh->nextx;
		end.y = hwh->nexty;
		r->distance = r->horizontal_hit;
		r->is_horizontal_hit = true;
	}
	else
	{
		end.x = vwh->nextx;
		end.y = vwh->nexty;
		r->distance = r->vertical_hit;
		r->is_horizontal_hit = false;
	}
	return (end);
}

void	draw_ray(t_cub3d *cub, t_ray *r)
{
	t_pixel	end;
	t_wallh	h_wall_hit;
	t_wallh	v_wall_hit;

	end = assign_hit(cub, r, &h_wall_hit, &v_wall_hit);
	end.color = RED;
	draw_line(cub->mmap, init_line(init_pixel(\
					cub->player->x * cub->mmap.ratio, \
					cub->player->y * cub->mmap.ratio, \
					RED), \
					init_pixel(end.x * cub->mmap.ratio, \
					end.y * cub->mmap.ratio, \
					RED)));
}