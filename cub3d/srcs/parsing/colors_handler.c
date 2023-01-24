/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:51:24 by fbily             #+#    #+#             */
/*   Updated: 2023/01/21 21:19:54 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	get_colors(t_parser *parser, int index)
{
	int	i;

	i = 1;
	if (ft_strlen(parser->tex_lines[index]) > 7
		&& parser->tex_lines[index][1] == ' ')
	{
		while (parser->tex_lines[index] && parser->tex_lines[index][i] == ' ')
			i++;
		if (parser->tex_lines[index][i] >= '0'
			&& parser->tex_lines[index][i] <= '9')
		{
			if (parser->tex_lines[index][0] == 'F')
				get_f(parser, index, i);
			else if (parser->tex_lines[index][0] == 'C')
				get_c(parser, index, i);
			return (true);
		}
	}
	ft_printf_fd(2, "Error\nProblem with colors description.\n");
	return (false);
}

void	get_f(t_parser *parser, int index, int i)
{
	if (parser->textures[F].path != NULL)
	{
		parser->textures[F].check = false;
		return ;
	}
	parser->textures[F].path = ft_substr(parser->tex_lines[index],
			i, (ft_strlen(parser->tex_lines[index]) - (i + 1)));
	if (parser->textures[F].path != NULL)
		parser->textures[F].check = true;
}

void	get_c(t_parser *parser, int index, int i)
{
	if (parser->textures[C].path != NULL)
	{
		parser->textures[C].check = false;
		return ;
	}
	parser->textures[C].path = ft_substr(parser->tex_lines[index],
			i, (ft_strlen(parser->tex_lines[index]) - (i + 1)));
	if (parser->textures[C].path != NULL)
		parser->textures[C].check = true;
}

bool	convert_colors(t_parser *parser, int id)
{
	char	tmp[4];
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (parser->textures[id].path[i])
	{
		j = 0;
		while (ft_isdigit(parser->textures[id].path[i]) && j < 3)
			tmp[j++] = parser->textures[id].path[i++];
		tmp[j] = '\0';
		if (parser->textures[id].path[i] && parser->textures[id].path[i] != ',')
		{
			ft_printf_fd(2, "Error\nProblem with color's values.\n");
			return (false);
		}
		if (check_convert(parser, tmp, id, k) == false)
			return (false);
		i++;
		k++;
	}
	return (true);
}

bool	check_convert(t_parser *parser, char *tmp, int id, int k)
{
	int	flag;

	flag = 0;
	parser->textures[id].colors[k] = ft_atouc(tmp, &flag);
	if (flag != 0)
	{
		ft_printf_fd(2, "Error\nColors values must be between 0 and 255.\n");
		return (false);
	}
	return (true);
}
