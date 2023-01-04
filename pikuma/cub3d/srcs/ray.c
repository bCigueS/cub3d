/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 10:19:20 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/04 12:26:17 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d(t_cub3d *cub);
void	init_ray_tab(t_cub3d *cub)
{
	int	i;
	double	ray_number = WINDOW_WIDTH / STRIP; 
	double	angle = cub->player->rangle - FOV / 2;
	double	increment_angle = FOV / ray_number;

	cub->tab_ray = (t_ray **)malloc(sizeof(t_ray *) * ray_number);
	if (!cub->tab_ray)
		return ;
	i = 0;
	while (i < ray_number)
	{
		cub->tab_ray[i] = init_ray(angle);
		angle += increment_angle;
		i++;
	}
}

t_ray	*init_ray(double angle)
{
	t_ray		*r;

	r = (t_ray *)malloc(sizeof(t_ray));
	if (!r)
		return (NULL);
	r->rangle = angle;
	if (r->rangle > 0 && r->rangle <= M_PI)
		r->ray_down = true;
	else
		r->ray_down = false;
	if (r->rangle <= (M_PI + M_PI / 2) && r->rangle >= M_PI / 2)
		r->ray_left = true;
	else
		r->ray_left = false;
	return (r);
}

void	update_ray(t_cub3d *cub)
{
	int			i;
	t_ray		*r;

	i = 0;
	while (i < WINDOW_WIDTH / STRIP)
	{
		r = cub->tab_ray[i++];
		r->rangle += cub->player->turn * cub->player->rspeed;
		if (r->rangle < 0)
			r->rangle = 2 * M_PI + r->rangle;
		else if (r->rangle >= 2 * M_PI) 
			r->rangle = r->rangle - M_PI * 2;
		if (r->rangle > 0 && r->rangle < M_PI)
			r->ray_down = true;
		else
			r->ray_down = false;
		if (r->rangle <= (M_PI + M_PI / 2) && r->rangle >= M_PI / 2)
			r->ray_left = true;
		else
			r->ray_left = false;
	}
}

bool	wall_found(t_cub3d *cub, t_wallh *wh, t_ray *r, int direction)
{
	/*
	if (direction == DOWN && !r->ray_down)
		wh->yintercept--;
	else if (direction == LEFT && r->ray_left)
		wh->xintercept--;
	*/
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
		{
			/*
			if (direction == DOWN)
				wh->nexty++;
			else if (direction == LEFT)
				wh->nextx++;
				*/
			return (true);
		}
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

bool	horizontal_hit(t_cub3d *cub, t_ray *r, t_wallh *wh)
{
	wh->yintercept = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	if (r->ray_down)
		wh->yintercept += TILE_SIZE;
	wh->xintercept = cub->player->x + (wh->yintercept - cub->player->y) /\
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

bool	vertical_hit(t_cub3d *cub, t_ray *r, t_wallh *wh)
{
	wh->xintercept = floor(cub->player->x / TILE_SIZE) * TILE_SIZE;
	if (!r->ray_left)
		wh->xintercept += TILE_SIZE;
	wh->yintercept = cub->player->y + (wh->xintercept - cub->player->x) *\
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

double		line_len(t_player *p, double x, double y)
{
	double distance;

	distance = (x - p->x) * (x - p->x) + (y - p->y) * (y - p->y);
	distance = floor(sqrt(distance));
	return (distance);
}

void	draw_ray(t_cub3d *cub, t_ray *r)
{
	t_pixel	end;
	t_wallh	h_wall_hit;
	t_wallh	v_wall_hit;

	end.color = BLACK;
	if (horizontal_hit(cub, r, &h_wall_hit))
		r->horizontal_hit = line_len(cub->player, h_wall_hit.nextx, \
				h_wall_hit.nexty);
	else
		r->horizontal_hit = 100000000;
	if (vertical_hit(cub, r, &v_wall_hit))
		r->vertical_hit = line_len(cub->player, v_wall_hit.nextx, \
				v_wall_hit.nexty);
	else
		r->vertical_hit = 100000000;
	if (r->horizontal_hit < r->vertical_hit)
	{
		end.x = h_wall_hit.nextx;
		end.y = h_wall_hit.nexty;
		r->distance = r->horizontal_hit;
	}
	else
	{
		end.x = v_wall_hit.nextx;
		end.y = v_wall_hit.nexty;
		r->distance = r->vertical_hit;
	}
	(void)end;
	/*
	draw_line(cub, init_line(init_pixel(cub->player->x, cub->player->y, RED), \
			end));				
			*/
}

void	draw_rays(t_cub3d *cub)
{
	int	i;
	double	ray_number = WINDOW_WIDTH / STRIP;

	i = 0;
	while (i < ray_number)
		draw_ray(cub, cub->tab_ray[i++]);
	draw_3d(cub);
}

void	draw_3d(t_cub3d *cub)
{
	int		i;
	int		j = 0;
	int		next = j;
	double	fov = FOV / 2;
	double	halfwindow = WINDOW_WIDTH / 2;
	double	wall_projection_distance = halfwindow / tan(fov);
	t_ray	*r;

	i = 0;
	(void)j;
	(void)next;
	while (i < WINDOW_WIDTH / STRIP)
	{
		r = cub->tab_ray[i];
		double correct_distance = cos(r->rangle - cub->player->rangle) * r->distance;
		double wall_height = (TILE_SIZE / correct_distance) * wall_projection_distance;
		i++;
		next = j + STRIP;
		while (j < next) {
			t_pixel	start = init_pixel(j, WINDOW_HEIGHT / 2 - (wall_height / 2), RED);
			t_pixel end = init_pixel(j, WINDOW_HEIGHT / 2 + (wall_height / 2), RED);
			draw_line(cub, init_line(start, end));
			j++;
		}
	}
}

// Soucis, quand la ligne est plus grande que windows_height
// Soh cah toa
