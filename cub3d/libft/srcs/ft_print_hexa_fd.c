/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:26:17 by fbily             #+#    #+#             */
/*   Updated: 2023/01/19 15:12:17 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	print_hexa_fd(int fd, va_list args, char c)
{
	int				len;
	unsigned int	nbr;

	nbr = (unsigned int)va_arg(args, unsigned int);
	len = hexa_size(nbr);
	if (c == 'x')
		putnbr_hexa_fd(fd, nbr);
	else if (c == 'X')
		putnbr_maj_hexa_fd(fd, nbr);
	return (len);
}

void	putnbr_hexa_fd(int fd, unsigned int nbr)
{
	char	*hexa;

	hexa = "0123456789abcdef\0";
	if (nbr / 16)
		putnbr_hexa_fd(fd, nbr / 16);
	print_char_fd(fd, hexa[nbr % 16]);
}

void	putnbr_maj_hexa_fd(int fd, unsigned int nbr)
{
	char	*hexa;

	hexa = "0123456789ABCDEF\0";
	if (nbr / 16)
		putnbr_maj_hexa_fd(fd, nbr / 16);
	print_char_fd(fd, hexa[nbr % 16]);
}
