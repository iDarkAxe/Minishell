/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:05:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/16 10:29:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

ssize_t	printn_fd(int fd, const char *str, size_t len);
ssize_t	print_fd(int fd, const char *str);

ssize_t	print_fd(int fd, const char *str)
{
	return (printn_fd(fd, str, ft_strlen(str)));
}

ssize_t	printn_fd(int fd, const char *str, size_t len)
{
	ssize_t	count;

	if (str == NULL)
		return (-1);
	count = write(fd, str, len);
	if (count == -1)
	{
		perror("write");
		ft_exit("1");
	}
	return (count);
}
