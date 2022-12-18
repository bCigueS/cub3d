/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:10:12 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/18 10:03:53 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define PRADIUS 5

typedef struct s_cub3d t_cub3d;

typedef struct	s_player {
	int	x;
	int	y;
	int	mspeed;
	int	turn;
	int	walk;
	int	size;
	double	rangle;
	double	rspeed;
}				t_player;

t_player	*create_player(int x, int y);
bool		init_player(t_cub3d *cub);
void		update_player(t_cub3d *cub);


#endif
