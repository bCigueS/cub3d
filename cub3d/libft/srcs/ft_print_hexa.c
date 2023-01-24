/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:26:17 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:46:30 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	print_hexa(va_list args, char c)
{
	int				len;
	unsigned int	nbr;

	nbr = (unsigned int)va_arg(args, unsigned int);
	len = hexa_size(nbr);
	if (c == 'x')
		putnbr_hexa(nbr);
	else if (c == 'X')
		putnbr_maj_hexa(nbr);
	return (len);
}

void	putnbr_hexa(unsigned int nbr)
{
	char	*hexa;

	hexa = "0123456789abcdef\0";
	if (nbr / 16)
		putnbr_hexa(nbr / 16);
	print_char(hexa[nbr % 16]);
}

void	putnbr_maj_hexa(unsigned int nbr)
{
	char	*hexa;

	hexa = "0123456789ABCDEF\0";
	if (nbr / 16)
		putnbr_maj_hexa(nbr / 16);
	print_char(hexa[nbr % 16]);
}

int	hexa_size(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 16;
		i++;
	}
	return (i);
}
