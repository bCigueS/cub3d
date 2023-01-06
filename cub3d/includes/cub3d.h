/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:21:57 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/06 10:41:51 by sbeylot          ###   ########.fr       */
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
# include "init_mlx.h"
# include "event.h"
# include "clean.h"
# include "drawing.h"
# include "player.h"
# include "ray.h"

/* --- CONSTANT --- */
# define MW 15
# define MH 15
# define WINDOW_WIDTH MW * TILE_SIZE 
# define WINDOW_HEIGHT MH * TILE_SIZE
# define FOV 50 * (M_PI / 180)
# define STRIP 1

/* --- MLX --- */
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define EXIT 17

/* --- xev -event keyboard --- */
# define KEY_ESC 65307
# define KEY_W 0x77
# define KEY_A 0x61
# define KEY_D 0x64
# define KEY_S 0x73
# define KEY_ARROW_LEFT 0xff51
# define KEY_ARROW_RIGHT 0xff53

typedef struct s_player t_player;
typedef struct s_ray	t_ray;

typedef struct	s_img
{
	void		*img;
	int			*addr;
	int			bpp;
	int			line_len;
	int			endian;
	double		ratio;
}				t_img;

typedef struct	s_player
{
	double			x;
	double			y;
	int			mspeed;
	int			turn;
	int			walk;
	double		straf;
	int			size;
	double		rangle;
	double		rspeed;
	t_img		img;
	int			icon_h;
	int			icon_w;
}				t_player;

typedef struct	s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_img		mmap;
	t_player	*player;
	int			**map;
	t_ray		*ray;
	t_ray		**tab_ray;
}				t_cub3d;

/* --- utils.c --- */

bool	is_a_wall(t_cub3d *cub, double x, double y);
void	normalise_angle(t_player *p);
double	line_len(t_player *p, double x, double y);

#endif