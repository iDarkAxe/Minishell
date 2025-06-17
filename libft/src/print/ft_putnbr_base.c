/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:31:04 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/10 12:09:10 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/**
 * @brief Putnbr with a particular base
 *
 * @param nbr number to print
 * @param base base to use
 * @return ssize_t number of char printed
 */
ssize_t	ft_putnbr_base(int nbr, const char *base)
{
	size_t		base_nbr;
	long int	nb;
	ssize_t		temp;

	temp = 0;
	nb = nbr;
	base_nbr = ft_check_base_putnbr(base);
	if (base_nbr < 1)
		return (0);
	if (nb < 0)
	{
		nb = -nb;
		temp += write(1, "-", 1);
	}
	if (nb >= (long int)base_nbr)
	{
		temp += ft_putnbr_base((int)(nb / (long int)base_nbr), base);
		temp += ft_putnbr_base((int)(nb % (long int)base_nbr), base);
	}
	else
		temp += write(1, &base[nb], 1);
	return (temp);
}

/**
 * @brief Putnbr for binary
 *
 * @param nbr number to print
 */
ssize_t	ft_putnbr_bin(int nbr)
{
	return (ft_putnbr_base(nbr, "01"));
}

/**
 * @brief Putnbr for octal
 *
 * @param nbr number to print
 */
ssize_t	ft_putnbr_oct(int nbr)
{
	return (ft_putnbr_base(nbr, "01234567"));
}

/**
 * @brief Putnbr for hex or HEX
 *
 * @param nbr number to print
 * @param height 1 for hex, 0 for HEX
 */
ssize_t	ft_putnbr_hex(int nbr, char height)
{
	if (height == 1 || height == 'x')
		return (ft_putnbr_base(nbr, "0123456789abcdef"));
	else
		return (ft_putnbr_base(nbr, "0123456789ABCDEF"));
}
