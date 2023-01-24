/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:40:54 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:45:56 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*back;
	char				*cp_s;
	unsigned int		i;

	i = 0;
	cp_s = (char *)s;
	if (start > ft_strlen(s))
	{
		back = ft_calloc(1, sizeof(char));
		if (back == NULL)
			return (NULL);
		return (back);
	}
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (len == ft_strlen(s))
		len = ft_strlen(s) - start;
	back = malloc(sizeof(char) * (len + 1));
	if (back == NULL)
		return (NULL);
	while (cp_s[start] && i < len)
		back[i++] = cp_s[start++];
	back[i] = '\0';
	return (back);
}
