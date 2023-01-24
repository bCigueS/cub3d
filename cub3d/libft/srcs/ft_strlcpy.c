/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:52:51 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:45:33 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_cpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_size;
	char	*cp_src;

	if (dest == NULL || src == NULL)
		return (0);
	cp_src = (char *)src;
	src_size = ft_strlen(src);
	if (src_size + 1 < size)
	{
		ft_cpy(dest, cp_src, src_size + 1);
	}
	else if (size != 0)
	{
		ft_cpy(dest, cp_src, size - 1);
		dest[size - 1] = '\0';
	}
	return (src_size);
}
