/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:49:03 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:45:30 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_size;
	size_t	dest_size;
	size_t	i;
	size_t	j;

	if (dest == NULL || src == NULL)
		return (0);
	src_size = ft_strlen(src);
	dest_size = ft_strlen(dest);
	i = dest_size;
	j = 0;
	if (size == 0)
		return (src_size);
	if (size < dest_size)
		return (src_size + size);
	while (src[j] && i < size - 1)
	{
		dest[i] = src [j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest_size + src_size);
}
