/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:27:29 by fbily             #+#    #+#             */
/*   Updated: 2022/12/05 15:25:15 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	which_print(char c, va_list args)
{
	int		len;

	len = 0;
	if (c == 'c')
		len = print_char((unsigned char)va_arg(args, int));
	else if (c == 's')
		len = print_str(va_arg(args, const char *));
	else if (c == 'd' || c == 'i')
		len = print_int(args);
	else if (c == 'u')
		len = print_unsigned_int(args);
	else if (c == 'x' || c == 'X')
		len = print_hexa(args, c);
	else if (c == 'p')
		len = print_ptr(args);
	else if (c == '%')
		len = print_char('%');
	else
		return (-1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	if (str == NULL)
		return (-1);
	va_start (args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += which_print(str[i + 1], args);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
