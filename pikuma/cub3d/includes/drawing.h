/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:55:25 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/04 14:34:20 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# define TILE_SIZE 128

# ifndef MW 
#  define MW 15
# endif

# ifndef MH 
#  define MH 15
# endif


/* --- COLOR --- */
# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define BLACK 0x000000


typedef struct s_img t_img;
typedef struct	s_pixel
{
	int			x;
	int			y;
	unsigned int			color;
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
	unsigned int color;
}				t_line;

void	draw_pixel(t_img img, t_pixel p);
void	draw_background(t_img img);
void	draw_rectangle(t_img img,int tx, int ty, int size);
void	draw_map(t_cub3d *cub);

/* --- draw_line.c --- */


void	draw_line(t_img img, t_line line);
t_line	init_line(t_pixel p1, t_pixel p2);
t_pixel	init_pixel(int x, int y, int color);

#endif