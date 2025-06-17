/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:14:17 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/06 11:50:04 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/**
 * @brief Print the string 's' on the file descriptor, followed by a newline
 *
 * @param s string to print
 * @param fd file descriptor
 * @return ssize_t number of char printed
 */
ssize_t	ft_putendl_fd(const char *s, int fd)
{
	return (ft_putstr_fd(s, fd) + write(fd, "\n", 1));
}

/**
 * @brief Print the string 's' on the file descriptor, followed by a newline
 * until a given size or the length of s if len is greater
 *
 * @param s string to print
 * @param len maximum char to be printed
 * @param fd file descriptor
 * @return ssize_t nombre de caractere qui ont été écrits
 */
ssize_t	ft_putnendl_fd(const char *s, size_t len, int fd)
{
	return (ft_putnstr_fd(s, len, fd) + write(fd, "\n", 1));
}
