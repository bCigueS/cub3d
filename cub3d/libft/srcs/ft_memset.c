/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:14:39 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:44:39 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*cp_s;

	if (s == NULL)
		return (NULL);
	cp_s = (unsigned char *)s;
	while (n-- > 0)
	{
		*cp_s = c;
		cp_s++;
	}
	return (s);
}
