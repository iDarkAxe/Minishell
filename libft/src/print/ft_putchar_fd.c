/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:09:32 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/06 11:49:42 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

ssize_t	ft_putchar_fd(const char c, int fd);

/**
 * @brief Print the character 'c' on the file descriptor
 *
 * @param c character to print
 * @param fd file descriptor
 * @return ssize_t number of char printed
 */
ssize_t	ft_putchar_fd(const char c, int fd)
{
	return (write(fd, &c, 1));
}
