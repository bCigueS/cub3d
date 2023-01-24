/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:13:06 by fbily             #+#    #+#             */
/*   Updated: 2023/01/23 21:25:03 by fbily            ###   ########.fr       */
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

bool	parse_map_h(t_parser *parser)
{
	int	i;
	int	j;

	i = 0;
	while (parser->map.map[i])
	{
		j = 0;
		while (parser->map.map[i][j])
		{
			if (i == 0 || i == parser->map.map_height)
			{
				if (parser->map.map[i][j] == ' '
					|| parser->map.map[i][j] == '1'
					|| parser->map.map[i][j] == '\n')
					j++;
				else
				{
					ft_printf_fd(2, "Error_h\nMap not surronded by wall.\n");
					return (false);
				}
			}
			else
			{
				if (parser->map.map[i][j] == ' '
					|| parser->map.map[i][j] == '1'
					|| parser->map.map[i][j] == '\n')
					j++;
				else if (parser->map.map[i][j] == '0'
					|| parser->map.map[i][j] == 'N')
				{
					if (parser->map.map[i][j + 1] == ' '
						|| parser->map.map[i][j + 1] == '\n')
					{
						ft_printf_fd(2, "Error_h\nBreach in a wall.\n");
						return (false);
					}
					j++;
				}
				else
				{
					ft_printf_fd(2, "Error_h\nUnrecognized character\n");
					return (false);
				}
			}
		}
		i++;
	}
	return (true);
}

bool	parse_map_v(t_parser *parser)
{
	int	i;
	int	j;

	j = 0;
	while (j < parser->map.map_widht)
	{
		i = 1;
		while (i < parser->map.map_height)
		{
			if (j == 0)
			{
				if (parser->map.map[i][j] == ' '
					|| parser->map.map[i][j] == '1')
					i++;
				else
				{
					ft_printf_fd(2, "Error_v\nMap not surronded by wall.\n");
					return (false);
				}
			}
			else if (j == (parser->map.map_widht - 1))
			{
				if (parser->map.map[i][j] == '\n')
					i++;
				else
				{
					ft_printf_fd(2, "Error_v\nMap not surronded by wall.\n");
					return (false);
				}
			}
			else
			{
				if (parser->map.map[i][j] == '1')
					i++;
				else if (parser->map.map[i][j] == ' ')
				{
					if (parser->map.map[i - 1][j] == ' '
					|| parser->map.map[i - 1][j] == '1')
						i++;
					else
					{
						ft_printf_fd(2, "Error_v\nBreach in a wall\n");
						return (false);
					}
				}
				else if (parser->map.map[i][j] == '0'
					|| parser->map.map[i][j] == 'N')
				{
					if (parser->map.map[i - 1][j] == ' ')
					{
						ft_printf_fd(2, "Error_v\nBreach in a wall.\n");
						return (false);
					}
					i++;
				}
				else
				{
					ft_printf_fd(2, "Error\nUnrecognized character\n");
					return (false);
				}
			}
		}
		j++;
	}
	return (true);
}

bool	check_map(t_parser *parser)
{
	find_max_len(parser);
	if (format_map(parser) == false)
		return (false);
	if (parse_map_h(parser) == false)
		return (false);
	if (parse_map_v(parser) == false)
		return (false);
	return (true);
}
