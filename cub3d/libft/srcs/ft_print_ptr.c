/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:47:24 by fbily             #+#    #+#             */
/*   Updated: 2022/09/20 17:46:40 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	print_ptr(va_list args)
{
	unsigned long long	ptr;
	int					len;

	ptr = (unsigned long long)va_arg(args, void *);
	if ((void *)ptr == NULL)
	{
		len = print_str("(nil)");
		return (len);
	}
	len = ptr_size(ptr);
	len += print_str("0x");
	putptr_hexa(ptr);
	return (len);
}

int	ptr_size(unsigned long long ptr)
{
	int	i;

	i = 0;
	while (ptr > 0)
	{
		ptr = ptr / 16;
		i++;
	}
	return (i);
}

void	putptr_hexa(unsigned long long nbr)
{
	char	*hexa;

	hexa = "0123456789abcdef\0";
	if (nbr / 16)
		putptr_hexa(nbr / 16);
	print_char(hexa[nbr % 16]);
}
