/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:16:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/10 12:13:23 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static ssize_t	ft_putnbr_recursive_fd(long long n, int fd);
ssize_t			ft_putnbr_fd(long long n, int fd);

/**
 * @brief Write the int 'n' on the given file descriptor
 *
 * @param n number to print
 * @param fd file descriptor
 * @return ssize_t number of char printed
 */
ssize_t	ft_putnbr_fd(long long n, int fd)
{
	ssize_t	count_printed;
	ssize_t	count_printed_temp;

	count_printed = 0;
	if (n < 0)
	{
		n = -n;
		count_printed = write(fd, "-", 1);
		if (count_printed < 0)
			return (count_printed);
	}
	count_printed_temp = ft_putnbr_recursive_fd(n, fd);
	if (count_printed_temp < 0)
		return (count_printed_temp);
	return (count_printed + count_printed_temp);
}

/**
 * @brief Write the int 'n' on the given file descriptor
 *	Works with recursion
 * @param n number to print
 * @param fd file descriptor
 * @return ssize_t number of char printed
 */
static ssize_t	ft_putnbr_recursive_fd(long long n, int fd)
{
	ssize_t	count_printed;
	ssize_t	count_printed_temp;
	char	temp;

	count_printed = 0;
	if (n >= 10)
	{
		count_printed = ft_putnbr_fd(n / 10, fd);
		if (count_printed < 0)
			return (count_printed);
	}
	temp = n % 10 + '0';
	count_printed_temp = write(fd, &temp, 1);
	if (count_printed_temp < 0)
		return (count_printed_temp);
	return (count_printed + count_printed_temp);
}

/**
 * @brief Print the integer ’n’ on the given file descriptor
 * @deprecated replaced by ft_printf ones
 * 
 * @param n integer to print
 * @param fd file descriptor
 * @return ssize_t number of char printed
 */
// ssize_t	ft_putnbr_fd(int n, int fd)
// {
// 	int		temp;
// 	ssize_t	count_printed;

// 	count_printed = 0;
// 	if (n < 0)
// 	{
// 		if (n == -2147483648)
// 			return (write(fd, "-2147483648", 11));
// 		else
// 		{
// 			n = -n;
// 			count_printed += write(fd, "-", 1);
// 		}
// 	}
// 	temp = n % 10 + '0';
// 	if (n >= 10)
// 	{
// 		count_printed += ft_putnbr_fd(n / 10, fd);
// 		count_printed += ft_putnbr_fd(n % 10, fd);
// 	}
// 	else
// 		return (write(fd, &temp, 1));
// 	return (count_printed);
// }
