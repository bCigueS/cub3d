/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:07:59 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/24 20:49:09 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d		cub;
	t_parser	parser;

	if (argc != 2)
		return (ft_printf_fd(STDERR_FILENO, "%s", USAGE), false);
	init_parsing(&parser, argv[1]);
	if (parsing(&parser) == false)
		return (-1);
	cub3d(&cub, &parser);
	return (0);
}
