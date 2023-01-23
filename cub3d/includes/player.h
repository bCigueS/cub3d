/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 07:32:50 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/23 10:27:58 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_player	t_player;

t_player	*init_player(t_cub3d *cub);
void		draw_player(t_cub3d *cub);
void		update_player(t_cub3d *cub);
bool		is_a_wall(t_cub3d *cub, double x, double y);

#endif
