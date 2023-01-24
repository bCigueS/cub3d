/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:47:24 by fbily             #+#    #+#             */
/*   Updated: 2023/01/19 15:12:32 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	print_ptr_fd(int fd, va_list args)
{
	unsigned long long	ptr;
	int					len;

	ptr = (unsigned long long)va_arg(args, void *);
	if ((void *)ptr == NULL)
	{
		len = print_str_fd(fd, "(nil)");
		return (len);
	}
	len = ptr_size(ptr);
	len += print_str_fd(fd, "0x");
	putptr_hexa_fd(fd, ptr);
	return (len);
}

void	putptr_hexa_fd(int fd, unsigned long long nbr)
{
	char	*hexa;

	hexa = "0123456789abcdef\0";
	if (nbr / 16)
		putptr_hexa_fd(fd, nbr / 16);
	print_char_fd(fd, hexa[nbr % 16]);
}
