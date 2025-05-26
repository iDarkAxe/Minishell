/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:07 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/26 17:54:57 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "file.h"
#include "garbage.h"
#include "minishell.h"

/**
 * @brief Create and redirect inputs and outputs needed for the command
 *
 * @param command command structure
 * @return int 0 or positive OK, negative ERROR
 */
int	handle_redirections(t_garbage *garbage, t_command *command,
	int fd_backup[2])
{
	if (!command || !command->tokens || !command->tokens->str)
		return (-1);
	if (command->file_error != 0)
		return (1);
	fd_backup[0] = 0;
	fd_backup[1] = 1;
	if (command->file_in)
	{
		fd_backup[0] = dup(0);
		read_write_to(garbage, command, 0);
	}
	if (command->file_out)
	{
		fd_backup[1] = dup(1);
		read_write_to(garbage, command, 1);
	}
	return (0);
}

/**
 * @brief Create and redirect inputs and outputs needed for the command
 *
 * @param command command structure
 * @return int 0 or positive OK, negative ERROR
 */
int	handle_redirections_forks(t_garbage *garbage, t_command *command)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (-1);
	if (command->file_error != 0)
		return (1);
	if (command->file_in)
		read_write_to(garbage, command, STDIN_FILENO);
	if (command->file_out)
		read_write_to(garbage, command, STDOUT_FILENO);
	if (command->file_error != 0)
		return (1);
	return (0);
}

/**
 * @brief Reset redirections by default values
 * Replace the new redirections by stdin and stdout
 *
 * @param command command structure
 * @param i value used for recursion
 */
void	reset_redirection(t_garbage *garbage, t_command *command,
	int fd_backup[2], unsigned char i)
{
	int	ret[2];

	if (!command || i > 1)
		return ;
	if (command->fd[i] != i)
	{
		ret[0] = dup2(fd_backup[i], i);
		if (ret[0] < 0)
			perror("minishell: dup2");
		ret[1] = close(fd_backup[i]);
		if (ret[1] != 0)
			perror("minishell: close");
		if (ret[0] < 0 || ret[1] != 0)
		{
			print_fd(1, "minishell: error on dup2 or close\n");
			ft_exit_int_np(garbage, EXIT_FAILURE);
		}
	}
	reset_redirection(garbage, command, fd_backup, i + 1);
	command->fd[i] = i;
	fd_backup[i] = i;
}
