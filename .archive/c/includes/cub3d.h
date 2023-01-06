/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:21:57 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/18 17:02:20 by sbeylot          ###   ########.fr       */
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
# include "player.h"
# include "drawing.h"
# include "map.h"
# include "ray.h"

# define TILE_SIZE 32

# ifndef MW
#  define MW 10
# endif

# ifndef MH
#  define MH 10
# endif

# define FOV 60 * (M_PI / 180) // Degree to radian

# define WINDOW_WIDTH  MW * TILE_SIZE
# define WINDOW_HEIGHT MH * TILE_SIZE
# define WALL_STRIP_WIDTH 4
# define RAY_NUMBER WINDOW_WIDTH / WALL_STRIP_WIDTH

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
# define KEY_ARROW_LEFT 0xff51
# define KEY_ARROW_RIGHT 0xff53

/* ---Structures --- */

typedef struct	s_player t_player;

typedef struct	s_img {
	void	*img;
	int		*addr;
	int 	bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_info t_info;

typedef struct	s_cub3d {
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_player	*player;
	int			**map;
	t_ray		**ray;
}				t_cub3d;

/* --- drawing.c --- */

/* --- player.c --- */

#endif
