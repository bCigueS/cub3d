/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:55:25 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/31 08:58:19 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# define TILE_SIZE 32

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

typedef struct	s_pixel
{
	int			x;
	int			y;
	unsigned int			color;
}				t_pixel;

void	draw_pixel(t_cub3d *cub, t_pixel p);
void	draw_background(t_cub3d *cub);
void	draw_rectangle(t_cub3d *cub,int tx, int ty, int size);
void	draw_map(t_cub3d *cub, int map[MH][MW]);

#endif
