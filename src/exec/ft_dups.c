/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:07 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/09 16:39:03 by ppontet          ###   ########lyon.fr   */
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
int	handle_redirections(t_command *command)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (-1);
	if (command->file_error != 0)
		return (1);
	if (command->file_in)
	{
		command->fd_backup[0] = dup(0);
		read_write_to(command, 0);
	}
	if (command->file_out)
	{
		command->fd_backup[1] = dup(1);
		read_write_to(command, 1);
	}
	return (0);
}

/**
 * @brief Create and redirect inputs and outputs needed for the command
 *
 * @param command command structure
 * @return int 0 or positive OK, negative ERROR
 */
int	handle_redirections_forks(t_command *command)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (-1);
	if (command->file_error != 0)
		return (1);
	if (command->file_in)
		read_write_to(command, STDIN_FILENO);
	if (command->file_out)
		read_write_to(command, STDOUT_FILENO);
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
void	reset_redirection(t_command *command, unsigned char i)
{
	int	ret[2];

	if (!command || i > 1)
		return ;
	if (command->fd[i] != i)
	{
		ret[0] = dup2(command->fd_backup[i], i);
		if (ret[0] < 0)
			perror("minishell: dup2");
		ret[1] = close(command->fd_backup[i]);
		if (ret[1] != 0)
			perror("minishell: close");
		if (ret[0] < 0 || ret[1] != 0)
		{
			print_fd(1, "minishell: error on dup2 or close\n");
			ft_exit_int_np(1);
		}
	}
	reset_redirection(command, i + 1);
	command->fd[i] = i;
	command->fd_backup[i] = i;
}
