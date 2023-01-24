/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:21:49 by flamby            #+#    #+#             */
/*   Updated: 2022/09/20 17:44:32 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cp_src;
	unsigned char	*cp_dest;
	size_t			i;

	if (dest == NULL || src == NULL)
		return (NULL);
	cp_src = (unsigned char *)src;
	cp_dest = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		cp_dest[i] = cp_src[i];
		i++;
	}
	return (dest);
}
