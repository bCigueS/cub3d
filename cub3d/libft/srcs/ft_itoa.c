/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:07:23 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:44:00 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_pos(char *back, long n)
{
	int		i;
	long	nb;

	i = 0;
	nb = n;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	nb = i;
	back = malloc(sizeof(char) * (i + 1));
	if (back == NULL)
		return (NULL);
	while (i > 0)
	{
		back[i - 1] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	back[nb] = '\0';
	return (back);
}

static char	*ft_neg(char *back, long n)
{
	int		i;
	long	nb;

	i = 0;
	n = -n;
	nb = n;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	back = malloc(sizeof(char) * (i + 2));
	if (back == NULL)
		return (NULL);
	i++;
	nb = i;
	back[0] = '-';
	while (i > 1)
	{
		back[i - 1] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	back[nb] = '\0';
	return (back);
}

char	*ft_itoa(int n)
{
	char	*back;
	long	nbr;

	nbr = n;
	back = 0;
	if (nbr == 0)
	{
		back = malloc(sizeof(char) * 2);
		if (back == NULL)
			return (NULL);
		back[0] = '0';
		back[1] = '\0';
		return (back);
	}
	if (nbr < 0)
		back = ft_neg(back, nbr);
	else
		back = ft_pos(back, nbr);
	return (back);
}	
