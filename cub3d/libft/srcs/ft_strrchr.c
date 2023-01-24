/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:47:45 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:45:50 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*cp_s;
	char	*back;

	i = 0;
	if (s == NULL)
		return (NULL);
	back = NULL;
	cp_s = (char *)s;
	while (cp_s[i])
	{
		if (cp_s[i] == (unsigned char)c)
			back = &cp_s[i];
		i++;
	}
	if ((unsigned char)c != '\0')
		return (back);
	else if ((unsigned char)c == '\0')
		return (&cp_s[ft_strlen(cp_s)]);
	else
		return (NULL);
}
