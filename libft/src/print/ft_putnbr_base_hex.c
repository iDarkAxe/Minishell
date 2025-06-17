/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:31:04 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/13 23:47:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/**
 * @brief Putnbr with a particular base
 *
 * @param nbr Number to be printed
 * @param base Base to be used
 * @param fd File descriptor
 * @return ssize_t number of char printed
 */
static ssize_t	ft_putnbr_hex_start(unsigned int nbr, const char *base, int fd)
{
	ssize_t	count;
	ssize_t	count_temp;
	ssize_t	count_temp2;

	count = 0;
	count_temp = 0;
	count_temp2 = 0;
	if (nbr >= 16)
	{
		count_temp = ft_putnbr_hex_start(nbr / 16, base, fd);
		if (count_temp < 0)
			return (count_temp);
		count_temp2 = ft_putnbr_hex_start(nbr % 16, base, fd);
		if (count_temp2 < 0)
			return (count_temp2);
	}
	else
		count = write(fd, &base[nbr], 1);
	return (count + count_temp + count_temp2);
}

/**
 * @brief Putnbr for hex or HEX
 *
 * @param nbr number to print
 * @param height 1 for hex, 0 for HEX
 * @param fd file descriptor
 * @return ssize_t number of char printed
 */
ssize_t	ft_putnbr_hex_fd(unsigned int nbr, char height, int fd)
{
	if (height == 1 || height == 'x')
		return (ft_putnbr_hex_start(nbr, "0123456789abcdef", fd));
	else
		return (ft_putnbr_hex_start(nbr, "0123456789ABCDEF", fd));
}

/**
 * @brief Putnbr with a particular base
 *
 * @param nbr Number to be printed
 * @param base Base to be used
 * @param fd File descriptor
 * @return ssize_t number of char printed
 */
static ssize_t	ft_putnbr_hex_pointer(unsigned long nbr, const char *base,
		int fd)
{
	ssize_t	temp;
	ssize_t	count_temp;
	ssize_t	count_temp2;

	temp = 0;
	count_temp = 0;
	count_temp2 = 0;
	if (nbr >= 16)
	{
		count_temp = ft_putnbr_hex_pointer(nbr / 16, base, fd);
		if (count_temp < 0)
			return (count_temp);
		count_temp2 = ft_putnbr_hex_pointer(nbr % 16, base, fd);
		if (count_temp2 < 0)
			return (count_temp2);
	}
	else
		temp = write(fd, &base[nbr], 1);
	return (temp + count_temp + count_temp2);
}

/**
 * @brief Print pointer adress
 *
 * @param nbr Number to be printed
 * @param fd File descriptor
 * @return ssize_t number of char printed
 */
ssize_t	ft_putptr_fd(unsigned long nbr, int fd)
{
	if (!nbr)
		return (write(fd, "(nil)", 5));
	if (write(fd, "0x", 2) != -1)
		return (ft_putnbr_hex_pointer(nbr, "0123456789abcdef\0", fd) + 2);
	return (-1);
}
