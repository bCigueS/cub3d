/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:41:40 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:44:59 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*cp_s;

	if (s == NULL)
		return (NULL);
	i = 0;
	cp_s = (char *)s;
	while (cp_s[i])
	{
		if (cp_s[i] == (unsigned char)c)
			return (&cp_s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return (&cp_s[ft_strlen(cp_s)]);
	else
		return (NULL);
}
