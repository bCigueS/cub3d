/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:55:25 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/23 12:46:53 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# define TILE_SIZE 64 
# define WINDOW 1
# define MINI_MAP 2

/* --- COLOR --- */
# define RED 0xFF0000
# define BLUE 0x00FF00
# define GREEN 0x0000FF
# define GOLD 0xFFD700
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define CEILLING 0xE3DACB
# define FLOOR 0xD1CC99

typedef struct s_img	t_img;
typedef struct s_pixel
{
	int				x;
	int				y;
	unsigned int	color;
}					t_pixel;

typedef struct s_line {
	t_pixel			p1;
	t_pixel			p2;
	unsigned int	x;
	unsigned int	y;
	int				dx;
	int				dy;
	int				xstep;
	int				ystep;
	int				err;
	int				err2;
	unsigned int	color;
}					t_line;

void	draw_pixel(t_cub3d *cub, t_pixel p, int option);
void	draw_background(t_cub3d *cub);
void	draw_rectangle(t_cub3d *cub, int tx, int ty, int size);
void	draw_map(t_cub3d *cub);
void	draw_ceiling_floor(t_cub3d *cub);

/* --- draw_line.c --- */

void	draw_line(t_cub3d *cub, t_line line);
t_line	init_line(t_pixel p1, t_pixel p2);
t_pixel	init_pixel(int x, int y, int color);



void	draw_line2(t_cub3d *cub, t_line line);

#endif
