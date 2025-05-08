/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:05:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/06 10:28:11 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include "garbage.h"

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
	{
		perror("write");
		free_garbage();
		exit(EXIT_FAILURE);
	}
	return (count);
}

/**
 * @brief Print the file descriptor of command into stderr
 * 
 * @param command command structure
 */
void	print_command_fd(t_command *command)
{
	char	*nbr;

	if (!command)
		return ;
	print_fd(2, "LIST OF FILE DESCRIPTORS : \nfd0 :");
	nbr = ft_itoa(command->fd[0]);
	print_fd(2, nbr);
	free(nbr);
	print_fd(2, "\nfd1 :");
	nbr = ft_itoa(command->fd[1]);
	print_fd(2, nbr);
	free(nbr);
	print_fd(2, "\nfd_backup0 :");
	nbr = ft_itoa(command->fd_backup[0]);
	print_fd(2, nbr);
	free(nbr);
	print_fd(2, "\nfd_backup1 :");
	nbr = ft_itoa(command->fd_backup[1]);
	print_fd(2, nbr);
	free(nbr);
	print_fd(2, "\n");
}
