/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:32:08 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/25 12:21:29 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

# define LOOK_UP 1
# define LOOK_DOWN 2
# define LOOK_LEFT 3
# define LOOK_RIGHT 4

void	open_close_door(t_cub3d *cub);
bool	init_door_tex(t_cub3d *cub);
void	clean_door_texture(t_cub3d *cub);

#endif
