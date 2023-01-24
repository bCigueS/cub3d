/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:23:55 by fbily             #+#    #+#             */
/*   Updated: 2023/01/24 17:58:03 by fbily            ###   ########.fr       */
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

void	init_parsing(t_parser *parser, char *argv)
{
	int	i;

	i = 0;
	parser->path_file = argv;
	parser->map.check_o = false;
	parser->map.orientation = '0';
	while (i <= C)
	{
		parser->textures[i].check = false;
		parser->textures[i].img = NULL;
		parser->textures[i].path = NULL;
		parser->textures[i].hexa_color = 0;
		i++;
	}
	parser->mlx = mlx_init();
	if (!parser->mlx)
	{
		ft_printf_fd(STDERR_FILENO, "Error\nMlx init failed.\n");
		exit(1);
	}
}
