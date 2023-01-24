/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:17:47 by flamby            #+#    #+#             */
/*   Updated: 2022/12/05 16:06:08 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	print_char_fd(int fd, unsigned char c)
{
	write(fd, &c, 1);
	return (1);
}

int	print_str_fd(int fd, const char *str)
{
	int			i;

	i = 0;
	if (str == NULL)
	{
		i = print_str_fd(fd, "(null)");
		return (i);
	}
	while (str[i])
		write(fd, &str[i++], 1);
	return (i);
}
