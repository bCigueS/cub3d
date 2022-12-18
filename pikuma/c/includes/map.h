/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 09:36:07 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/18 11:13:59 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# ifndef MW
#  define MW 10
# endif

# ifndef MH
#  define MH 10
# endif

int		**init_map(int map[MH][MW]);
bool	is_not_wall(int **map, int x, int y);
void	clean_map(int **map, int index);

#endif
