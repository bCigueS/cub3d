/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:26:31 by flamby            #+#    #+#             */
/*   Updated: 2022/09/20 17:44:36 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*cp_dest;
	unsigned char	*cp_src;
	size_t			i;

	if (dest == NULL || src == NULL)
		return (NULL);
	cp_dest = (unsigned char *)dest;
	cp_src = (unsigned char *)src;
	if (src > dest)
	{
		i = -1;
		while (++i < n)
			cp_dest[i] = cp_src[i];
	}
	else if (src < dest)
	{
		while (n > 0)
		{
			cp_dest[n - 1] = cp_src[n - 1];
			n--;
		}
	}
	return (cp_dest);
}
