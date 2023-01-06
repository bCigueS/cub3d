/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:12:23 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/17 16:29:18 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H


/* --- COLOR --- */
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GREY	0x424242
# define RED	0xFF0000

typedef struct	s_cub3d t_cub3d;

typedef struct	s_pixel {
	int x;
	int y;
	int color;
}				t_pixel;

typedef struct	s_line {
	t_pixel	p1;
	t_pixel	p2;
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	xstep;
	int	ystep;
	int	err;
	int	err2;
	int color;
}				t_line;

/* --- drawing.c --- */
void	draw_pixel(t_cub3d *cub, t_pixel pix);
void	draw_grid(t_cub3d *cub);
void	draw_rectangle(t_cub3d *cub, int posx, int posy, int size);
void	draw_wall(t_cub3d *cub);
void	draw_background(t_cub3d *cub);

void	draw_player(t_cub3d *cub);
void	draw_player_direction(t_cub3d *cub);
bool	init_player(t_cub3d *cub);

/* --- drawing_line.c --- */
t_pixel	init_pixel(int x, int y, int color);
t_line	init_line(t_pixel p1, t_pixel p2);
void	draw_line(t_cub3d *cub, t_line line);



#endif
