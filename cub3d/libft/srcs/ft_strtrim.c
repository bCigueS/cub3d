/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:22:05 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:45:53 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	inset(char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

static int	get_start(char *str, char *set)
{
	int	i;

	i = 0;
	while (inset(set, str[i]) == 1)
		i++;
	return (i);
}

static int	get_end(char *str, char *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > 0 && inset(set, str[i]) == 1)
		i--;
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		size;
	int		i;
	char	*back;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = get_start((char *)s1, (char *)set);
	size = ((get_end((char *)s1, (char *)set)) - start) + 1;
	if (size <= 1)
	{
		back = ft_calloc(1, sizeof(char));
		if (back == NULL)
			return (NULL);
		return (back);
	}
	back = malloc(sizeof(char) * size);
	if (back == NULL)
		return (NULL);
	i = 0;
	while (i < (size - 1))
		back[i++] = s1[start++];
	back[i] = '\0';
	return (back);
}
