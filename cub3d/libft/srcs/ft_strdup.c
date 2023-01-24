/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:59:29 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:45:03 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*cp_s;

	if (s == NULL)
		return (NULL);
	cp_s = (char *)s;
	dest = malloc((sizeof(char)) * (ft_strlen(cp_s) + 1));
	if (dest == NULL)
		return (0);
	ft_memcpy(dest, cp_s, ft_strlen(cp_s) +1);
	return (dest);
}
