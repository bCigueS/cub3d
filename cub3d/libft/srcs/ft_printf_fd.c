/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:27:29 by fbily             #+#    #+#             */
/*   Updated: 2022/12/05 15:53:52 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	which_print_fd(int fd, char c, va_list args)
{
	int		len;

	len = 0;
	if (c == 'c')
		len = print_char_fd(fd, (unsigned char)va_arg(args, int));
	else if (c == 's')
		len = print_str_fd(fd, va_arg(args, const char *));
	else if (c == 'd' || c == 'i')
		len = print_int_fd(fd, args);
	else if (c == 'u')
		len = print_unsigned_int_fd(fd, args);
	else if (c == 'x' || c == 'X')
		len = print_hexa_fd(fd, args, c);
	else if (c == 'p')
		len = print_ptr_fd(fd, args);
	else if (c == '%')
		len = print_char_fd(fd, '%');
	else
		return (-1);
	return (len);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	if (str == NULL || fd < 0 || fd > 1024)
		return (-1);
	va_start (args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += which_print_fd(fd, str[i + 1], args);
			i++;
		}
		else
		{
			write(fd, &str[i], 1);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
