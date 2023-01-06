/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 09:34:16 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/18 11:13:58 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_map(int **map, int index)
{
	int	i;

	i = index;
	while (i >= 0)
	{
		free(map[i]);
		i--;
	}
	free(map);
}

int	**init_map(int map[MH][MW])
{
	int	i;
	int	**pmap;

	i = 0;
	pmap = (int **)malloc(sizeof(int *) * MH);
	if (!pmap)
		return (NULL);
	while (i < MH)
	{
		pmap[i] = ft_calloc(MW, sizeof(int));
		if (!pmap[i])
			return (clean_map(pmap, i), NULL); // Add un clean
		for (int j = 0; j < MW; j++) {
			pmap[i][j] = map[i][j];
		}
		i++;
	}
	return (pmap);
}

bool is_not_wall(int **map, int x, int y)
{
	int xpos;
	int	ypos;

	xpos = x / TILE_SIZE;
	ypos = y / TILE_SIZE;
	if (map[ypos][xpos] == 0)
		return (true);
	if (map[ypos][xpos] == 80)
		return (true);
	return (false);
}
