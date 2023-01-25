/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:37:34 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/25 15:28:11 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	texture_color_vertical(t_cub3d *cub, t_rcinfo rci,
		t_ray *r, int y_coo)
{
	t_texture		*tex;
	unsigned int	tex_x;
	unsigned int	tex_y;

	if (cub->map[r->wh_index_y][r->wh_index_x] == 68)
		tex = cub->door_to_show;
	else if (!r->is_horizontal_hit && r->ray_left)
		tex = &cub->texture[2];
	else
		tex = &cub->texture[3];
	tex_y = (y_coo * tex->icon_h) / floor(rci.wall_height);
	tex_x = r->end.y / TILE_SIZE * TILE_SIZE;
	tex_x = r->end.y - tex_x;
	if (r->ray_left)
		tex_x = TILE_SIZE - tex_x;
	tex_x = (tex_x * tex->icon_w) / TILE_SIZE;
	if (tex_x >= 0 && tex_x < (unsigned int)tex->icon_w && tex_y >= 0 && \
			tex_y < (unsigned int)tex->icon_h)
		return (tex->img.addr[tex_x + tex->icon_w * tex_y]);
	else
		return (tex->img.addr[tex_x - 1 + (tex->icon_w * tex_y - 1)]);
}

static unsigned int	texture_color_horizontal(t_cub3d *cub, t_rcinfo rci, \
		t_ray *r, int y_coo)
{
	t_texture		*tex;
	unsigned int	tex_x;
	unsigned int	tex_y;

	if (cub->map[r->wh_index_y][r->wh_index_x] == 68)
		tex = cub->door_to_show;
	else if (r->is_horizontal_hit && r->ray_down)
		tex = &cub->texture[1];
	else
		tex = &cub->texture[0];
	tex_y = (y_coo * tex->icon_h) / floor(rci.wall_height);
	tex_x = r->end.x / TILE_SIZE * TILE_SIZE;
	tex_x = r->end.x - tex_x;
	if (r->ray_down)
		tex_x = TILE_SIZE - tex_x;
	tex_x = (tex_x * tex->icon_w) / TILE_SIZE;
	if (tex_x >= 0 && tex_x < (unsigned int)tex->icon_w && tex_y >= 0 && \
			tex_y < (unsigned int)tex->icon_h)
		return (tex->img.addr[tex_x + tex->icon_w * tex_y]);
	else
		return (tex->img.addr[tex_x - 1 + (tex->icon_w * tex_y - 1)]);
}

static unsigned int	choose_color(t_cub3d *cub, t_rcinfo rci, \
		t_ray *r, int y_coo)
{
	unsigned int	color;

	if (r->is_horizontal_hit && r->ray_down)
		color = texture_color_horizontal(cub, rci, r, y_coo);
	else if (r->is_horizontal_hit && !r->ray_down)
		color = texture_color_horizontal(cub, rci, r, y_coo);
	else if (!r->is_horizontal_hit && r->ray_left)
		color = texture_color_vertical(cub, rci, r, y_coo);
	else if (!r->is_horizontal_hit && !r->ray_left)
		color = texture_color_vertical(cub, rci, r, y_coo);
	else
		color = 0xffffff;
	return (color);
}

static void	raycasting_draw_wall_texture(t_cub3d *cub, t_rcinfo rci, \
		t_ray *r, int *pi)
{
	int		next;
	double	y;
	double	y_coo;

	next = *pi + STRIP;
	while (*pi < next)
	{
		y = 0;
		y_coo = WINDOW_HEIGHT / 2 - (rci.wall_height / 2) + y;
		while (y_coo < 0)
			y_coo = WINDOW_HEIGHT / 2 - (rci.wall_height / 2) + y++;
		while (y_coo < WINDOW_HEIGHT)
		{
			draw_pixel(cub, init_pixel(*pi, y_coo, \
						choose_color(cub, rci, r, y)), WINDOW);
			y += 1;
			y_coo = WINDOW_HEIGHT / 2 - (rci.wall_height / 2) + y;
			if (y >= rci.wall_height)
				break ;
		}
		*pi += 1;
	}
}

void	raycasting(t_cub3d *cub)
{
	int			i;
	int			pixel_index;
	t_rcinfo	rayc;
	t_ray		*r;

	i = 0;
	pixel_index = 0;
	rayc.fov = cub->info.fov / 2;
	rayc.halfwindow = WINDOW_WIDTH / 2;
	rayc.wall_projection_distance = rayc.halfwindow / tan(rayc.fov);
	while (i < WINDOW_WIDTH / STRIP)
	{
		r = cub->tab_ray[i++];
		rayc.correct_distance = cos(r->rangle - cub->player->rangle) * \
							r->distance;
		rayc.wall_height = (TILE_SIZE / rayc.correct_distance) * \
							rayc.wall_projection_distance;
		raycasting_draw_wall_texture(cub, rayc, r, &pixel_index);
	}
}
