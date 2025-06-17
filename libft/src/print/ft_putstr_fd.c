/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:12:07 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/10 12:11:52 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

/**
 * @brief Print the string 's' on the file descriptor
 *
 * @param s string to print
 * @param fd file descriptor
 * @return ssize_t nombre de caractere qui ont été écrits
 */
ssize_t	ft_putstr_fd(const char *s, int fd)
{
	if (s == NULL)
		return (write(fd, "(null)", 6));
	return (write(fd, s, ft_strlen(s)));
}

/**
 * @brief Print the string 's' on the file descriptor until a given size
 * or the length of s if len is greater
 * 
 * @param s string to print
 * @param len maximum char to be printed
 * @param fd  nombre de caractere qui ont été écrits
 * @return ssize_t nombre de caractere qui ont été écrits
 */	
ssize_t	ft_putnstr_fd(const char *s, size_t len, int fd)
{
	if (s == NULL)
		return (write(fd, "(null)", 6));
	if (len > ft_strlen(s))
		return (write(fd, s, ft_strlen(s)));
	else
		return (write(fd, s, len));
}
