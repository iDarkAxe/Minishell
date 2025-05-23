/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:05:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/23 11:13:13 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

ssize_t	printn_fd(int fd, const char *str, size_t len);
ssize_t	print_fd(int fd, const char *str);

/**
 * @brief Function used to write safely and exits if write failed
 *
 * @param fd file descriptor
 * @param str string to print
 * @return ssize_t number of character printed
 */
ssize_t	print_fd(int fd, const char *str)
{
	return (printn_fd(fd, str, ft_strlen(str)));
}

// HACK Should we exit if a write has an error ?
/**
 * @brief Function used to write safely and exits if write failed
 *
 * @param fd file descriptor
 * @param str string to print
 * @param len number of character to print
 * @return ssize_t number of character printed
 */
ssize_t	printn_fd(int fd, const char *str, size_t len)
{
	ssize_t	count;

	if (str == NULL)
		return (-1);
	count = write(fd, str, len);
	if (count < 0)
		perror("write");
	return (count);
}
