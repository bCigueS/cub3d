/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:50:02 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:45:41 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	size;
	size_t	i;
	char	*back;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	if (s[i] == '\0')
		return (back = ft_strdup(s));
	size = ft_strlen(s);
	back = malloc(sizeof(char) * (size +1));
	if (back == NULL)
		return (NULL);
	while (i < size)
	{
		back[i] = f(i, s[i]);
		i++;
	}
	back[i] = '\0';
	return (back);
}
