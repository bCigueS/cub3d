/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:59:08 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:44:27 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cp_s;
	size_t			i;

	if (s == NULL)
		return (NULL);
	cp_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (cp_s[i] == (unsigned char)c)
			return (&cp_s[i]);
		i++;
	}
	return (NULL);
}
