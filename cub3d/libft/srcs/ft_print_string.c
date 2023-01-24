/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:17:47 by flamby            #+#    #+#             */
/*   Updated: 2022/09/20 17:46:43 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	print_char(unsigned char c)
{
	write(1, &c, 1);
	return (1);
}

int	print_str(const char *str)
{
	int			i;

	i = 0;
	if (str == NULL)
	{
		i = print_str("(null)");
		return (i);
	}
	while (str[i])
		write(1, &str[i++], 1);
	return (i);
}
