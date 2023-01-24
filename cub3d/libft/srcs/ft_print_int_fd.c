/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:45:21 by fbily             #+#    #+#             */
/*   Updated: 2023/01/19 15:12:26 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	print_int_fd(int fd, va_list args)
{
	int	len;
	int	nbr;

	nbr = va_arg(args, int);
	if (nbr == -2147483648)
	{
		len = print_str_fd(fd, "-2147483648");
		return (len);
	}
	else if (nbr < 0 && nbr != -2147483648)
	{
		nbr = -nbr;
		len = int_size(nbr) + 1;
		ft_putnbr_int_fd(fd, -nbr);
		return (len);
	}
	len = int_size(nbr);
	ft_putnbr_int_fd(fd, nbr);
	return (len);
}

void	ft_putnbr_int_fd(int fd, int nb)
{	
	if (nb >= 0 && nb < 10)
		print_char_fd(fd, nb + 48);
	else if (nb < 0)
	{
		print_char_fd(fd, '-');
		ft_putnbr_int_fd(fd, -nb);
	}
	else
	{
		ft_putnbr_int_fd(fd, nb / 10);
		ft_putnbr_int_fd(fd, nb % 10);
	}
}

int	print_unsigned_int_fd(int fd, va_list args)
{
	int				len;
	unsigned int	nbr;

	nbr = va_arg(args, unsigned int);
	len = int_size(nbr);
	ft_putnbr_unsigned_int_fd(fd, nbr);
	return (len);
}

void	ft_putnbr_unsigned_int_fd(int fd, unsigned int nb)
{	
	if (nb < 10)
		print_char_fd(fd, nb + 48);
	else
	{
		ft_putnbr_unsigned_int_fd(fd, nb / 10);
		ft_putnbr_unsigned_int_fd(fd, nb % 10);
	}
}
