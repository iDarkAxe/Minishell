/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:05:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/15 17:22:15 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

ssize_t	print_fd(int fd, const char *str)
{
	ssize_t	len;

	if (str == NULL)
		return (-1);
	len = write(fd, str, ft_strlen(str));
	if (len == -1)
	{
		perror("write");
		ft_exit("1");
	}
	return (len);
}
