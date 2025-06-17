/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:58:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/10 12:21:13 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static ssize_t	ft_print_search(int fd, char param, va_list va);
static ssize_t	ft_verify_param(const char **str, int fd, va_list va);

/**
 * @brief Works similarly as printf without handling size format
 *
 * @param str String to be printed
 * @param ... Variadic arguments
 * @return int Returns the number of characters printed or -1 if error
 */
int	ft_printf(const char *str, ...)
{
	va_list	arg_ptr;
	ssize_t	write_count;
	size_t	count;

	count = 0;
	if (str == NULL || (str[0] == '%' && str[1] == '\0'))
		return (-1);
	va_start(arg_ptr, str);
	while (*str != '\0')
	{
		write_count = ft_verify_param(&str, 1, arg_ptr);
		if (write_count < 0)
			return ((int)write_count);
		count += (size_t)write_count;
	}
	va_end(arg_ptr);
	return ((int)count);
}

/**
 * @brief Works similarly as printf without handling size format
 *
 * @param fd File descriptor
 * @param str String to be printed
 * @param ... Variadic arguments
 * @return int Returns the number of characters printed or -1 if error
 */
int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	arg_ptr;
	ssize_t	write_count;
	size_t	count;

	count = 0;
	if (str == NULL || (str[0] == '%' && str[1] == '\0'))
		return (-1);
	va_start(arg_ptr, str);
	while (*str != '\0')
	{
		write_count = ft_verify_param(&str, fd, arg_ptr);
		if (write_count < 0)
			return ((int)write_count);
		count += (size_t)write_count;
	}
	va_end(arg_ptr);
	return ((int)count);
}

/**
 * @brief Verify if the param after the percentage exist
 *
 * @param str String currently testing
 * @return char returns param if exist in printf, 0 if doesn´t
 */
static ssize_t	ft_verify_param(const char **str, int fd, va_list va)
{
	ssize_t	ret;
	char	format;

	if ((*str)[0] != '%')
	{
		ret = ft_putchar_fd((*str)[0], fd);
		(*str)++;
		return (ret);
	}
	format = (*str)[1];
	if (format == '\0')
	{
		(*str)++;
		return (-1);
	}
	if (format == 'c' || format == 's' || format == 'p' || format == 'd'
		|| format == 'i' || format == 'u' || format == 'x' || format == 'X'
		|| format == '%')
	{
		(*str) += 2;
		return (ft_print_search(fd, format, va));
	}
	(*str) += 2;
	return (-1);
}

/**
 * @brief Executes the right function for the right param
 *
 * @param fd File descriptor
 * @param param Character after the percentage
 * @param va Variadic arguments
 */
static ssize_t	ft_print_search(int fd, char param, va_list va)
{
	if (param == '%')
		return (ft_putchar_fd('%', fd));
	if (param == 'c')
		return (ft_putchar_fd((char)va_arg(va, int), fd));
	if (param == 's')
		return (ft_putstr_fd(va_arg(va, char *), fd));
	if (param == 'p')
		return (ft_putptr_fd((unsigned long)va_arg(va, long long), fd));
	if (param == 'd' || param == 'i')
		return (ft_putnbr_fd(va_arg(va, int), fd));
	if (param == 'u')
		return (ft_putnbr_fd(va_arg(va, unsigned int), fd));
	if (param == 'x' || param == 'X')
		return (ft_putnbr_hex_fd(va_arg(va, unsigned int), param, fd));
	return (-1);
}
