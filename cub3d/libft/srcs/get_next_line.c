/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:32:07 by fbily             #+#    #+#             */
/*   Updated: 2023/01/18 18:59:14 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl_list	*stash[1024];
	char				*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, line, 0) < 0)
		return (NULL);
	read_and_stash(fd, &stash[fd]);
	if (stash[fd] == NULL)
		return (NULL);
	line = extract_line(stash[fd]);
	clean_stash(&stash[fd]);
	if (line[0] == '\0')
	{
		free_stash(stash[fd]);
		stash[fd] = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

/* Uses read() to add characters to the stash */
void	read_and_stash(int fd, t_gnl_list **stash)
{
	int		byte_read;
	char	*buf;

	byte_read = 1;
	while (found_newline(*stash) == 0 && byte_read > 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		byte_read = read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && byte_read == 0) || byte_read == -1)
		{
			free(buf);
			return ;
		}
		buf[byte_read] = '\0';
		add_to_stash(stash, buf, byte_read);
		free (buf);
	}
}

/* Adds the content of our buffer to the end of our stash */
void	add_to_stash(t_gnl_list **stash, char *buf, int byte_read)
{
	t_gnl_list	*last;
	t_gnl_list	*new_node;
	int			i;

	new_node = malloc(sizeof(t_gnl_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->line = malloc(sizeof(char) * (byte_read + 1));
	if (new_node->line == NULL)
		return ;
	i = 0;
	while (buf[i] && i < byte_read)
	{
		new_node->line[i] = buf[i];
		i++;
	}
	new_node->line[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
}

/* Extracts all characters from our stash and stores them in out line.
 * stopping after the first \n it encounters */
char	*extract_line(t_gnl_list *stash)
{
	int		i;
	int		j;
	char	*line;

	if (stash == NULL)
		return (NULL);
	line = generate_line(stash);
	i = 0;
	while (stash)
	{
		j = 0;
		while (stash->line[j])
		{
			if (stash->line[j] == '\n')
			{
				line[i] = stash->line[j];
				i++;
				break ;
			}
			line[i++] = stash->line[j++];
		}
		stash = stash->next;
	}
	line[i] = '\0';
	return (line);
}

/* After extracting the line that was read, we don't need those characters
 * anymore. This function clears the stash so only the characters that have
 * not been returned at the end of get_next_line remain in our static stash. */
void	clean_stash(t_gnl_list **stash)
{
	t_gnl_list	*last;
	t_gnl_list	*fresh_node;
	size_t		i;
	size_t		j;

	fresh_node = malloc(sizeof(t_gnl_list));
	if (fresh_node == NULL || stash == NULL)
		return ;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->line[i] && last->line[i] != '\n')
		i++;
	if (last->line && last->line[i] == '\n')
		i++;
	fresh_node->line = malloc(sizeof(char) * ((ft_strlen(last->line) - i) + 1));
	if (fresh_node->line == NULL)
		return ;
	j = 0;
	while (last->line[i])
		fresh_node->line[j++] = last->line[i++];
	fresh_node->line[j] = '\0';
	free_stash(*stash);
	fresh_node->next = NULL;
	*stash = fresh_node;
}
