/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:19:27 by fbily             #+#    #+#             */
/*   Updated: 2023/01/23 18:11:23 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	main(int argc, char **argv)
{
	t_parser	parser;
	int			i;

	if (argc != 2)
	{
		ft_printf_fd(STDERR_FILENO, "%s", USAGE);
		return (false);
	}
	init_parsing(&parser, argv[1]);
	if (parsing(&parser) == false)
		return (-1);
	else
	{
		i = 0;
		free_map(parser.tex_lines);
		while (i < 4)
			printf("Mlx img : %p\n", parser.textures[i++].img);
		while (i < 6)
			printf("Colors : 0x%x\n", parser.textures[i++].hexa_color);
		printf("\n\n");
		print_map(parser.map.map);
	}
	free_map(parser.map.map);
	return (0);
}

// Protection strdup dans divide_file ??
// map empty ??