/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:45:21 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:46:38 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	int_size(long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	print_int(va_list args)
{
	int	len;
	int	nbr;

	nbr = va_arg(args, int);
	if (nbr == -2147483648)
	{
		len = print_str("-2147483648");
		return (len);
	}
	else if (nbr < 0 && nbr != -2147483648)
	{
		nbr = -nbr;
		len = int_size(nbr) + 1;
		ft_putnbr_int(-nbr);
		return (len);
	}
	len = int_size(nbr);
	ft_putnbr_int(nbr);
	return (len);
}

void	ft_putnbr_int(int nb)
{	
	if (nb >= 0 && nb < 10)
		print_char(nb + 48);
	else if (nb < 0)
	{
		print_char('-');
		ft_putnbr_int(-nb);
	}
	else
	{
		ft_putnbr_int(nb / 10);
		ft_putnbr_int(nb % 10);
	}
}

int	print_unsigned_int(va_list args)
{
	int				len;
	unsigned int	nbr;

	nbr = va_arg(args, unsigned int);
	len = int_size(nbr);
	ft_putnbr_unsigned_int(nbr);
	return (len);
}

void	ft_putnbr_unsigned_int(unsigned int nb)
{	
	if (nb < 10)
		print_char(nb + 48);
	else
	{
		ft_putnbr_unsigned_int(nb / 10);
		ft_putnbr_unsigned_int(nb % 10);
	}
}
