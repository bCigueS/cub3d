/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:21:57 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/25 10:18:13 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ---Library--- */
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <time.h>
# include <errno.h>

# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"
# include "init_mlx.h"
# include "event.h"
# include "clean.h"
# include "drawing.h"
# include "player.h"
# include "ray.h"
# include "parsing.h"
# include "door.h"

/* --- CONSTANT --- */
# define MW 15
# define MH 15
# define WINDOW_WIDTH 1280 
# define WINDOW_HEIGHT 920

# define FOV 50 
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
# define KEY_SPACE 0x20

typedef struct s_player	t_player;
typedef struct s_ray	t_ray;

typedef struct s_img
{
	void		*img;
	int			*addr;
	int			bpp;
	int			line_len;
	int			endian;
	double		ratio;
}				t_img;

typedef struct s_texture
{
	t_img		img;
	int			icon_w;
	int			icon_h;
}				t_texture;

typedef struct s_player
{
	double		x;
	double		y;
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

typedef struct s_info
{
	int				map_col;
	int				map_row;
	int				map_dim_w;
	int				map_dim_h;
	double			fov;
	double			player_orientation;
	unsigned int	ceilling;
	unsigned int	floor;
}					t_info;

typedef struct s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_img		mmap;
	t_player	*player;
	int			**map;
	t_ray		**tab_ray;
	t_texture	*texture;
	t_texture	*door;
	t_texture	*door_to_show;
	t_info		info;
	t_parser	*parser;
}				t_cub3d;

int		render(void *param);
bool	cub3d(t_cub3d *cub, t_parser *parser);

/* --- utils.c --- */
bool	is_a_wall(t_cub3d *cub, double x, double y);
void	normalise_angle(t_player *p);
double	line_len(t_player *p, double x, double y);
double	normalise_angle2(double angle);
double	degree_to_radian(double angle);

/* --- utils2.c --- */
bool	is_a_void(t_cub3d *cub, int x, int y);
void	colission_index(t_ray *r);
double	get_minimap_ratio(t_cub3d *cub);
void	player_stepback(t_player *p);

#endif
