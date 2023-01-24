/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:19:16 by fbily             #+#    #+#             */
/*   Updated: 2023/01/24 17:58:55 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "parsing.h"

# define USAGE "Usage : ./cub3d [path_to_map_description]\n"

enum e_ids
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
};

typedef struct s_tex
{
	bool				check;
	void				*img;
	int					width;
	int					height;
	char				*path;
	unsigned char		colors[3];
	unsigned int		hexa_color;
}				t_tex;

typedef struct s_map
{
	char				**map;
	char				orientation;
	int					map_height;
	int					map_widht;
	bool				check_o;
	bool				door;
}				t_map;

typedef struct s_parser
{
	char				**file;
	char				**tex_lines;
	char				*path_file;
	int					file_lines;
	t_map				map;
	t_tex				textures[6];
	void				*mlx;
}				t_parser;

/***************************		PARSING.C		***************************/
bool	read_textures(t_parser *parser);
bool	test_textures(t_parser *parser);
bool	check_file(t_parser *parser);
bool	check_map(t_parser *parser);
bool	parsing(t_parser *parser);

/***************************	FILE_HANDLER.C		***************************/
int		count_lignes(char *file_path);
bool	divide_file(t_parser *parser);
bool	get_file(t_parser *parser);

/***************************		CLEAN.C		***************************/
void	print_map(char **map);
void	free_map(char **map);

/***************************	COLORS_HANDLER.C	***************************/
bool	check_convert(t_parser *parser, char *tmp, int id, int k);
void	get_f(t_parser *parser, int index, int i);
void	get_c(t_parser *parser, int index, int i);
bool	convert_colors(t_parser *parser, int id);
bool	get_colors(t_parser *parser, int index);

/***************************	TEXTURES_HANDLER.C	***************************/
bool	check_textures(t_parser *parser);
bool	handle_textures(t_parser *parser, int index);
void	get_textures(t_parser *parser, int index, int id);

/***************************	PARSING_MAP.C	***************************/
bool	check_orientation(t_parser *parser, int i, int j);
bool	parse_middle(t_parser *parser, int i, int j);
bool	check_ground(char **map, int i, int j);
bool	check_door(char **map, int i, int j);
bool	parse_map(t_parser *parser);

/***************************	PARSING_MAP_UTILS.C	***************************/
bool	resize_line(t_parser *parser, int k);
void	find_max_len(t_parser *parser);
bool	format_map(t_parser *parser);
bool	is_bordure(char c);
bool	is_player(char c);

/***************************	UTILS_PARSING.C	***************************/
void	init_parsing(t_parser *parser, char *argv);
void	stock_colors(t_parser *parser);
void	print_map(char **map);

#endif
/* 
Contraintes :

- Rien apres la map
- "Error\n" + Message explicite

Info :
- Chaque info separee par 1 ou + '\n'
- Orde aleatoire
- Chaque info peut comporter X espace entre chaque element.
- Liste ID : NO / SO / WE / EA / F / C

F & C :
- (char *)ID + (int)tab[0] in range [0,255]

Textures :
- (char *)ID + (char *)path_to_textures

Map :
- 6 caracteres only : 0 & 1 + [N / S / E / W] (= orientation joueur)
- Entouree de murs [1]
- Gerer espace autour de la map
- 
 */

/* 

typedef struct s_tex
{
	void	*img;
	int		width;
	int		height;
}				t_tex;

tex.img = mlx_xpm_file_to_image(vars->mlx, "textures/FILE.xpm",
			&vars->tex.width, &vars->tex.height); 
            

*/
