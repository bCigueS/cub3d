/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:50:31 by fbily             #+#    #+#             */
/*   Updated: 2023/01/21 20:25:56 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	handle_textures(t_parser *parser, int index)
{
	if (ft_strlen(parser->tex_lines[index]) < 8)
	{
		ft_printf_fd(2, "Error\nProblem with texture's description.\n");
		return (false);
	}
	if (parser->tex_lines[index][0] == 'N'
		&& parser->tex_lines[index][1] == 'O')
		get_textures(parser, index, NO);
	else if (parser->tex_lines[index][0] == 'S'
		&& parser->tex_lines[index][1] == 'O')
		get_textures(parser, index, SO);
	else if (parser->tex_lines[index][0] == 'W'
		&& parser->tex_lines[index][1] == 'E')
		get_textures(parser, index, WE);
	else if (parser->tex_lines[index][0] == 'E'
		&& parser->tex_lines[index][1] == 'A')
		get_textures(parser, index, EA);
	else
	{
		ft_printf_fd(2, "Error\nProblem with texture's description.\n");
		return (false);
	}
	return (true);
}

void	get_textures(t_parser *parser, int index, int id)
{
	int	i;

	i = 2;
	if (parser->textures[id].path != NULL)
	{
		parser->textures[id].check = false;
		return ;
	}
	if (parser->tex_lines[index][2] && parser->tex_lines[index][2] == ' ')
	{
		while (parser->tex_lines[index] && parser->tex_lines[index][i] == ' ')
			i++;
		if (parser->tex_lines[index][i] == '.')
		{
			parser->textures[id].path = ft_substr(parser->tex_lines[index],
					i, (ft_strlen(parser->tex_lines[index]) - (i + 1)));
			if (parser->textures[id].path != NULL)
			{
				parser->textures[id].check = true;
				return ;
			}
		}
	}
}

bool	check_textures(t_parser *parser)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (parser->textures[i].check == false)
			return (false);
		i++;
	}
	return (true);
}
