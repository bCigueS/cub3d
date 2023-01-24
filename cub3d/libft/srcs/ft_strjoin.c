/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:21:31 by fbily             #+#    #+#             */
/*   Updated: 2022/10/08 21:05:01 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*back;
	size_t	size;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = (ft_strlen(s1) + ft_strlen(s2) + 1);
	back = (char *)malloc(sizeof(char) * size);
	if (!back)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		back[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		back[i + j] = s2[j];
		j++;
	}
	back[i + j] = '\0';
	return (back);
}
