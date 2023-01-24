/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:07:59 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/24 18:16:39 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	//t_cub3d		cub;
	t_parser	parser;
	int			i;

	if (argc != 2)
		return (ft_printf_fd(STDERR_FILENO, "%s", USAGE), false);
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
	//cub3d(&cub, &parser);
	free_map(parser.map.map);
	return (0);
}
