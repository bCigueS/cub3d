/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:32:10 by fbily             #+#    #+#             */
/*   Updated: 2023/01/19 19:32:54 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 100

# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_gnl_list
{
	char				*line;
	struct s_gnl_list	*next;
}					t_gnl_list;

char		*get_next_line(int fd);
void		read_and_stash(int fd, t_gnl_list **stash);
void		add_to_stash(t_gnl_list **stash, char *buf, int byte_read);
char		*extract_line(t_gnl_list *stash);
void		clean_stash(t_gnl_list **stash);
int			found_newline(t_gnl_list *stash);
t_gnl_list	*ft_lst_get_last(t_gnl_list *stash);
char		*generate_line(t_gnl_list *stash);
void		free_stash(t_gnl_list *stash);

#endif