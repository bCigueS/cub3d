/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 09:37:34 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/16 11:55:40 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
static void	choose_color(t_ray *r, t_pixel *start, t_pixel *end)
{
	unsigned int color;

	if (r->is_horizontal_hit && r->ray_down)
		color = RED;
	else if (r->is_horizontal_hit && !r->ray_down)
		color = GREEN;
	else if (!r->is_horizontal_hit && r->ray_left)
		color = BLUE;
	else if (!r->is_horizontal_hit && !r->ray_left)
		color = GOLD;
	else 
		color = BLACK;

	start->color = color;
	end->color = color;
}

static void	raycasting_draw_wall(t_cub3d *cub, t_rcinfo rci, t_ray *r, int *pi)
{
	int		next;
	t_pixel	start;
	t_pixel	end;

	next = *pi + STRIP;
	choose_color(r, &start, &end);
	while (*pi < next)
	{
		start = init_pixel(*pi, WINDOW_HEIGHT / 2 - (rci.wall_height / 2), \
				start.color);
		end = init_pixel(*pi, WINDOW_HEIGHT / 2 + (rci.wall_height / 2), \
				end.color);
		draw_line(cub->img, init_line(start, end));
		*pi += 1;
	}
}
*/


static unsigned int texture_color_vertical(t_cub3d *cub, t_rcinfo rci, t_ray *r, int y_coo)
{
	t_texture	*tex;
	int			tex_x;
	int			tex_y;

	if (!r->is_horizontal_hit && r->ray_left)
		tex = &cub->texture[2];
	else 
		tex = &cub->texture[3];
	tex_y = (y_coo * tex->icon_h) / floor(rci.wall_height);
	tex_x = r->end.y / TILE_SIZE * TILE_SIZE;
	tex_x = r->end.y - tex_x;
	if (r->ray_left)
		tex_x = TILE_SIZE - tex_x;
	tex_x = (tex_x * tex->icon_w) / TILE_SIZE;
	//
	// C'est la couleur que je cherche
	if (tex_x >= 0 && tex_x < tex->icon_w && tex_y >= 0 && tex_y < tex->icon_h)
		return (tex->img.addr[tex_x + tex->icon_w * tex_y]);
	else
		return (tex->img.addr[tex_x - 1 + tex->icon_w * tex_y - 1]);
		//return (0x000000);
}

static unsigned int texture_color_horizontal(t_cub3d *cub, t_rcinfo rci, t_ray *r, int y_coo)
{
	t_texture	*tex;
	int			tex_x;
	int			tex_y;

	if (r->is_horizontal_hit && r->ray_down)
		tex = &cub->texture[1];
	else
		tex = &cub->texture[0];
	tex_y = (y_coo * tex->icon_h) / floor(rci.wall_height); 
	tex_x = r->end.x / TILE_SIZE * TILE_SIZE; 
	tex_x = r->end.x - tex_x;
	if (r->ray_down)
		tex_x = TILE_SIZE - tex_x;
	tex_x = (tex_x * tex->icon_w) / TILE_SIZE;


	// C'est la couleur que je cherche
	if (tex_x >= 0 && tex_x < tex->icon_w && tex_y >= 0 && tex_y < tex->icon_h)
		return (tex->img.addr[tex_x + tex->icon_w * tex_y]);
	else
		return (tex->img.addr[tex_x - 1 + tex->icon_w * tex_y - 1]);
		//return (0x000000);
}
static unsigned int	choose_color(t_cub3d *cub, t_rcinfo rci, t_ray *r, int y_coo)
{
	unsigned int color;

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

static void	raycasting_draw_wall_texture(t_cub3d *cub, t_rcinfo rci, t_ray *r, int *pi)
{
	int	next;
	
	next = *pi + STRIP;
	while (*pi < next)
	{
		double y = 0;
		while (y < rci.wall_height)
		{
			draw_pixel(cub->img, init_pixel(*pi, (WINDOW_HEIGHT / 2 - (rci.wall_height / 2)) + y, \
			choose_color(cub, rci, r, y)));
			y += 1;
		}
		*pi += 1;
	}
}

static void	init_rcinfo(t_rcinfo *rci)
{
	rci->fov = FOV / 2;
	rci->halfwindow = WINDOW_WIDTH / 2;
	rci->wall_projection_distance = rci->halfwindow / tan(rci->fov);
}

void	raycasting(t_cub3d *cub)
{
	int			i;
	int			pixel_index;
	int			pixel_index2;
	t_rcinfo	rayc;
	t_ray		*r;

	i = 0;
	pixel_index = 0;
	pixel_index2 = 0;
	init_rcinfo(&rayc);
	while (i < WINDOW_WIDTH / STRIP)
	{
		r = cub->tab_ray[i++];
		rayc.correct_distance = cos(r->rangle - cub->player->rangle) * \
							r->distance;
		rayc.wall_height = (TILE_SIZE / rayc.correct_distance) * \
							rayc.wall_projection_distance;
		//raycasting_draw_wall(cub, rayc, r, &pixel_index);
		raycasting_draw_wall_texture(cub, rayc, r, &pixel_index2);
	}
}
