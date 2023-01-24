/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:41:47 by fbily             #+#    #+#             */
/*   Updated: 2022/12/05 16:11:58 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>

/*************************		PRINTF		*************************/
int		ft_printf(const char *str, ...);
int		which_print(char c, va_list args);
int		print_char(unsigned char c);
int		print_str(const char *str);
int		print_int(va_list args);
int		int_size(long nb);
int		hexa_size(unsigned int nbr);
int		print_unsigned_int(va_list args);
int		print_ptr(va_list args);
int		ptr_size(unsigned long long ptr);
int		print_hexa(va_list args, char c);
void	ft_putnbr_int(int nb);
void	ft_putnbr_unsigned_int(unsigned int nb);
void	putnbr_hexa(unsigned int nbr);
void	putptr_hexa(unsigned long long nbr);
void	putnbr_maj_hexa(unsigned int nbr);

/*************************		PRINTF_FD		*************************/
int		ft_printf_fd(int fd, const char *str, ...);
int		which_print_fd(int fd, char c, va_list args);
int		print_char_fd(int fd, unsigned char c);
int		print_str_fd(int fd, const char *str);
int		print_int_fd(int fd, va_list args);
int		print_unsigned_int_fd(int fd, va_list args);
int		print_ptr_fd(int fd, va_list args);
int		print_hexa_fd(int fd, va_list args, char c);
void	ft_putnbr_int_fd(int fd, int nb);
void	ft_putnbr_unsigned_int_fd(int fd, unsigned int nb);
void	putnbr_hexa_fd(int fd, unsigned int nbr);
void	putptr_hexa_fd(int fd, unsigned long long nbr);
void	putnbr_maj_hexa_fd(int fd, unsigned int nbr);
int		int_size(long nb);
int		hexa_size(unsigned int nbr);
int		ptr_size(unsigned long long ptr);

#endif