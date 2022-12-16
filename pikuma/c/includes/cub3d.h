/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:21:57 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/16 16:51:27 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ---Library--- */
# include "libft.h"
# include "../mlx/mlx.h"
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <time.h>

# define TILE_SIZE 32
# define MW	10
# define MH 10

# define FPS 60
# define FPMS	1000 / FPS

# define PRADIUS 5

# define WINDOW_WIDTH  MW * TILE_SIZE
# define WINDOW_HEIGHT MH * TILE_SIZE

# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GREY	0x424242
# define RED	0xFF0000

/* --- ERROR --- */
# define MLX_ERROR -10

/* --- MLX --- */
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5
# define EXIT 17


/* --- xev -event keyboard --- */
# define KEY_ESC 65307
# define KEY_W 0x77
# define KEY_A 0x61
# define KEY_D 0x64
# define KEY_S 0x73

/* ---Structures --- */

typedef struct	s_img {
	void	*img;
	int		*addr;
	int 	bpp;
	int		line_len;
	int		endian;
}				t_img;

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

typedef struct	s_player {
	int	x;
	int	y;
	int	mspeed;
	int	rspeed;
	int	size;
	double	rangle;
}				t_player;

typedef struct	s_cub3d {
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_player	*player;
	int			**map;
	int			loop;
}				t_cub3d;

/* --- drawing.c --- */
void	draw_pixel(t_cub3d *cub, t_pixel pix);
void	draw_grid(t_cub3d *cub);
void	draw_rectangle(t_cub3d *cub, int posx, int posy, int size);
void	draw_wall(t_cub3d *cub);
void	draw_background(t_cub3d *cub);

void	draw_player(t_cub3d *cub);
bool	init_player(t_cub3d *cub);

/* --- drawing_line.c --- */
t_pixel	init_pixel(int x, int y, int color);
t_line	init_line(t_pixel p1, t_pixel p2);
void	draw_line(t_cub3d *cub, t_line line);

/* --- player.c --- */
t_player	*create_player(int x, int y);
bool		init_player(t_cub3d *cub);

#endif
