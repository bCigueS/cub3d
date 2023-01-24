/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:40:39 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:43:45 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*back;
	long	f_size;

	back = NULL;
	if (size > 0 && size * nmemb / size != nmemb)
		return (NULL);
	f_size = nmemb * size;
	if (f_size == 0)
	{
		back = malloc(sizeof(char));
		if (back == NULL)
			return (NULL);
		return (back);
	}
	back = malloc(f_size);
	if (back == NULL)
		return (NULL);
	ft_memset(back, 0, f_size);
	return (back);
}
