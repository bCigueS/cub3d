/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:32:09 by fbily             #+#    #+#             */
/*   Updated: 2023/01/18 18:59:38 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

/* Looks for a newline character in the given linked list. */
int	found_newline(t_gnl_list *stash)
{
	t_gnl_list	*actual;
	int			i;

	if (stash == NULL)
		return (0);
	i = 0;
	actual = ft_lst_get_last(stash);
	while (actual->line[i])
	{
		if (actual->line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/* Returns a pointer to the last node in our stash */
t_gnl_list	*ft_lst_get_last(t_gnl_list *stash)
{
	t_gnl_list	*last;

	last = stash;
	while (last && last->next != NULL)
		last = last->next;
	return (last);
}

/* Calculates the number of chars in the current line, including the trailing
 * \n if there is one, and allocates memory accordingly. */
char	*generate_line(t_gnl_list *stash)
{
	int		i;
	int		j;
	char	*line;

	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->line[i])
		{
			if (stash->line[i] == '\n')
			{
				j++;
				break ;
			}
			i++;
			j++;
		}
		stash = stash->next;
	}
	line = malloc(sizeof(char) * (j + 1));
	if (line == NULL)
		return (NULL);
	return (line);
}

/* Frees the entire stash. */
void	free_stash(t_gnl_list *stash)
{
	t_gnl_list	*actual;
	t_gnl_list	*next;

	actual = stash;
	while (actual)
	{
		free(actual->line);
		next = actual->next;
		free (actual);
		actual = next;
	}
}
