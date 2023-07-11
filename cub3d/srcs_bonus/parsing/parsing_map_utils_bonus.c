/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:32:26 by fbily             #+#    #+#             */
/*   Updated: 2023/01/24 18:16:13 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_max_len(t_parser *parser)
{
	int	i;
	int	len;

	i = 0;
	while (parser->map.map[i])
	{
		len = (int)ft_strlen(parser->map.map[i]);
		if (len > parser->map.map_widht)
			parser->map.map_widht = len;
		i++;
	}
}

bool	format_map(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser->map.map[i])
	{
		if ((int)ft_strlen(parser->map.map[i]) < parser->map.map_widht)
			if (resize_line(parser, i) == false)
				return (false);
		i++;
	}
	return (true);
}

bool	resize_line(t_parser *parser, int k)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) + (parser->map.map_widht + 1));
	if (!new)
		return (false);
	while (i < ((int)ft_strlen(parser->map.map[k]) - 1))
	{
		new[i] = parser->map.map[k][i];
		i++;
	}
	while (i < (parser->map.map_widht - 1))
		new[i++] = ' ';
	new[parser->map.map_widht - 1] = '\n';
	new[parser->map.map_widht] = '\0';
	free(parser->map.map[k]);
	parser->map.map[k] = new;
	return (true);
}

bool	is_bordure(char c)
{
	if (c == '1' || c == ' ' || c == '\n')
		return (true);
	else
		return (false);
}

bool	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	else
		return (false);
}
