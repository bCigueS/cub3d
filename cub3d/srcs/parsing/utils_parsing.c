/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:23:55 by fbily             #+#    #+#             */
/*   Updated: 2023/01/24 20:54:50 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

void	free_map_until(char **map, int k)
{
	int	i;

	i = 0;
	while (i < k)
		free(map[i++]);
	free(map);
}

void	stock_colors(t_parser *parser)
{
	int	i;

	i = F;
	while (i <= C)
	{
		parser->textures[i].hexa_color |= parser->textures[i].colors[0] << 16;
		parser->textures[i].hexa_color |= parser->textures[i].colors[1] << 8;
		parser->textures[i].hexa_color |= parser->textures[i].colors[2];
		i++;
	}
}

void	clean_parsing(t_parser *parser)
{
	int	i;

	i = 0;
	while (i <= C)
	{
		if (parser->textures[i].img != NULL)
			mlx_destroy_image(parser->mlx, parser->textures[i].img);
		if (parser->textures[i].path != NULL)
			free(parser->textures[i].path);
		i++;
	}
	if (parser->mlx != NULL)
		mlx_destroy_display(parser->mlx);
	free(parser->mlx);
}

void	init_parsing(t_parser *parser, char *argv)
{
	int	i;

	i = 0;
	parser->path_file = argv;
	parser->map.check_o = false;
	parser->map.door = false;
	parser->map.orientation = '0';
	parser->map.map_widht = 0;
	parser->map.map_height = 0;
	while (i <= C)
	{
		parser->textures[i].check = false;
		parser->textures[i].img = NULL;
		parser->textures[i].path = NULL;
		parser->textures[i].hexa_color = 0;
		parser->textures[i].colors[0] = 0;
		parser->textures[i].colors[1] = 0;
		parser->textures[i].colors[2] = 0;
		i++;
	}
}
