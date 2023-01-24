/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:17:35 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:45:47 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*cp_big;
	char	*cp_little;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	cp_big = (char *)big;
	cp_little = (char *)little;
	if (cp_little[i] == '\0')
		return (cp_big);
	while (i < len && cp_big[i])
	{
		j = 0;
		k = i;
		while (cp_big[k] == cp_little[j] && k < len)
		{
			k++;
			j++;
			if (cp_little[j] == '\0')
				return (&cp_big[k - j]);
		}
		i++;
	}
	return (NULL);
}
