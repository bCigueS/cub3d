/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:11:32 by fbily             #+#    #+#             */
/*   Updated: 2023/01/24 20:11:00 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	get_file(t_parser *parser)
{
	int	i;
	int	fd;

	i = 0;
	parser->file_lines = count_lignes(parser->path_file);
	if (parser->file_lines == -1)
		return (false);
	parser->file = malloc(sizeof(char *) * (parser->file_lines + 1));
	if (!parser->file)
		return (ft_printf_fd(STDERR_FILENO, "Error\nMalloc failed.\n"), false);
	fd = open(parser->path_file, O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, "Error\n", 7);
		perror("open ");
		return (free_map(parser->file), false);
	}
	while (42)
	{
		parser->file[i] = get_next_line(fd);
		if (parser->file[i] == NULL)
			break ;
		i++;
	}
	return (close(fd), true);
}

int	count_lignes(char *file_path)
{
	char	*line;
	int		fd;
	int		count;

	count = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, "Error\n", 7);
		perror("open ");
		return (-1);
	}
	while (42)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count++;
		free(line);
	}
	close(fd);
	free(line);
	return (count);
}

static int	get_first_part(t_parser *parser)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	parser->tex_lines = malloc(sizeof(char *) * 7);
	if (!parser->tex_lines)
		return (ft_printf_fd(STDERR_FILENO, "Error\nMalloc failed.\n"), -1);
	while (j < 6 && parser->file[i])
	{
		if (parser->file[i][0] == '\n')
			i++;
		else
		{
			parser->tex_lines[j] = ft_strdup(parser->file[i]);
			if (!parser->tex_lines[j])
				return (free_map_until(parser->map.map, 6), false);
			i++;
			j++;
		}
	}
	parser->tex_lines[6] = NULL;
	return (i);
}

static bool	get_map(t_parser *parser, int i, int j)
{
	while (parser->file[i])
	{
		if (parser->file[i][0] == '\n')
			i++;
		else
			break ;
	}
	parser->map.map_height = parser->file_lines - i;
	parser->map.map = malloc(sizeof(char *) * (parser->map.map_height + 1));
	if (!parser->map.map)
		return (ft_printf_fd(STDERR_FILENO, "Error\nMalloc failed.\n"), false);
	j = 0;
	while (i < parser->file_lines)
	{
		parser->map.map[j] = ft_strdup(parser->file[i]);
		if (!parser->map.map[j])
			return (free_map_until(parser->map.map, parser->map.map_height),
				false);
		i++;
		j++;
	}
	parser->map.map[j] = NULL;
	return (true);
}

bool	divide_file(t_parser *parser)
{
	int	i;
	int	j;

	j = 0;
	i = get_first_part(parser);
	if (i == -1)
	{
		free_map(parser->file);
		clean_parsing(parser);
		return (false);
	}
	if (get_map(parser, i, j) == false)
	{
		free_map(parser->file);
		free_map(parser->tex_lines);
		clean_parsing(parser);
		return (false);
	}
	free_map(parser->file);
	return (true);
}
