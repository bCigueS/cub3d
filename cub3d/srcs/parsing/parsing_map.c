/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:13:06 by fbily             #+#    #+#             */
/*   Updated: 2023/01/24 20:52:23 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_ground(char **map, int i, int j)
{
	if ((map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
		|| (map[i][j + 1] == ' ' || map[i][j - 1] == ' '))
	{
		ft_printf_fd(2, "Error\nFind breach in the map.\n");
		return (false);
	}
	else if ((map[i - 1][j] == '\n' || map[i + 1][j] == '\n')
		|| (map[i][j - 1] == '\n' || map[i][j + 1] == '\n'))
	{
		ft_printf_fd(2, "Error\nFind breach in the map.\n");
		return (false);
	}
	return (true);
}

bool	check_orientation(t_parser *parser, int i, int j)
{
	if (check_ground(parser->map.map, i, j) == false)
		return (false);
	if (parser->map.check_o == true)
	{
		ft_printf_fd(2, "Error\nMultiple player position detected.\n");
		return (false);
	}
	parser->map.check_o = true;
	parser->map.orientation = parser->map.map[i][j];
	return (true);
}

bool	check_door(char **map, int i, int j)
{
	if (((map[i + 1][j] == '1' && map[i - 1][j] == '1')
		&& ((map[i][j + 1] == '0' || is_player(map[i][j + 1]) == true)
		&& (map[i][j - 1] == '0' || is_player(map[i][j - 1] == true)))))
		return (true);
	else if (((map[i + 1][j] == '0' || is_player(map[i + 1][j] == true))
		&& (map[i - 1][j] == '0' || is_player(map[i - 1][j]) == true))
			&& (map[i][j + 1] == '1' && map[i][j - 1] == '1'))
		return (true);
	else
	{
		ft_printf_fd(2, "Error\nDoors should be between walls.\n");
		return (false);
	}
}

bool	parse_middle(t_parser *parser, int i, int j)
{
	if (is_bordure(parser->map.map[i][j]) == true)
		return (true);
	else if (parser->map.map[i][j] == '0')
	{
		if (check_ground(parser->map.map, i, j) == false)
			return (false);
	}
	else if (is_player(parser->map.map[i][j]) == true)
	{
		if (check_orientation(parser, i, j) == false)
			return (false);
	}
	else if (parser->map.map[i][j] == 'D')
	{
		if (check_door(parser->map.map, i, j) == false)
			return (false);
		parser->map.door = true;
	}
	else
	{
		ft_printf_fd(2, "Error_h\nUnrecognized character\n");
		return (false);
	}
	return (true);
}

bool	parse_map(t_parser *parser)
{
	int	i;
	int	j;

	i = 0;
	while (parser->map.map[i])
	{
		j = 0;
		while (parser->map.map[i][j])
		{
			if ((i == 0 || i == parser->map.map_height)
				|| (j == 0 || j == (parser->map.map_widht - 1)))
			{
				if (is_bordure(parser->map.map[i][j]) == false)
					return (ft_printf_fd(2, "Error\nWall incomplete.\n"), false);
			}
			else if (parse_middle(parser, i, j) == false)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
