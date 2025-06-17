/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:10:56 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/06 11:51:23 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Print pointer adress
 *
 * @param ptr pointer to print
 * @return ssize_t number of char printed
 */
ssize_t	ft_putpointer_fd(const void *ptr)
{
	if (!ptr)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	return (2 + ft_putnbr_hex(((int)(unsigned long)ptr), 'x'));
}
