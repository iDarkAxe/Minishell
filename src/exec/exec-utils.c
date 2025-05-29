/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:32:27 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/29 11:08:45 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

size_t	count_commands(t_command *command);
int		safe_close(int *fd);
void	dup_and_close(t_garbage *garbage, int oldfd, int newfd);
int		needs_to_be_forked(t_command *command);

/**
 * @brief Cound the number of commands in the command structure
 * 
 * @param command command structure
 * @return size_t number of commands
 */
size_t	count_commands(t_command *command)
{
	size_t		nbr_cmds;
	t_command	*current;

	nbr_cmds = 0;
	current = command;
	while (current)
	{
		nbr_cmds++;
		current = current->next;
	}
	return (nbr_cmds);
}

/**
 * @brief Safely close fd
 * 
 * @param fd file descriptor to close
 * @return 0 no error, 1 ERROR
 */
int	safe_close(int *fd)
{
	if (fd == NULL)
		return (1);
	if (*fd != -1)
	{
		if (close(*fd) != 0)
		{
			perror("minishell: close");
			return (1);
		}
		*fd = -1;
	}
	return (0);
}

/**
 * @brief Special dup2 that also closes the old fd
 * 
 * @param oldfd fd that will overwrite newfd and will be close
 * @param newfd fd to overwrite by oldfd
 */
void	dup_and_close(t_garbage *garbage, int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		free_garbage(garbage);
		exit(1);
	}
	close(oldfd);
}

/**
 * @brief Check if it needs to be forked
 *
 * @param command command structure
 * @return int 0 NO, 1 YES
 */
int	needs_to_be_forked(t_command *command)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (0);
	if (ft_strncmp(command->tokens->str, "|", 2) == 0)
		return (1);
	if (command->next && command->next->tokens
		&& ft_strncmp(command->next->tokens->str, "|", 2) == 0)
		return (1);
	return (0);
}
