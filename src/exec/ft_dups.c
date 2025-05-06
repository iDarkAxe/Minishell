/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:07 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/06 10:28:42 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "file.h"
#include "builtins.h"
#include "garbage.h"

static int	create_pipe(t_command *command);

// WIP try to handle pipes

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
	if (command->next && command->next->tokens
		&& ft_strncmp(command->next->tokens->str, "|", 2) == 0)
		create_pipe(command);
	if (ft_strncmp(command->tokens->str, "|", 2) == 0)
	{
		command->fd_backup[0] = dup(0);
		command->fd[0] = command->pipe_fd[1];
		dup2(command->fd[0], 0);
	}
	if (command->file_in)
		read_write_to(command, 0);
	if (command->file_out)
		read_write_to(command, 1);
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
	int	ret[3];

	if (!command || i > 1)
		return ;
	if (command->fd[i] != i)
	{
		ret[0] = close(command->fd[i]);
		if (ret[0] != 0)
			perror("minishell: close");
		ret[1] = dup2(command->fd_backup[i], i);
		if (ret[1] < 0)
			perror("minishell: dup2");
		ret[2] = close(command->fd_backup[i]);
		if (ret[2] != 0)
			perror("minishell: close");
		if (ret[0] != 0 || ret[1] < 0 || ret[2] != 0)
		{
			print_fd(1, "minishell: error on close or dup2\n");
			ft_exit_int(1);
		}
	}
	reset_redirection(command, i + 1);
	fd_default(command);
}

/**
 * @brief Change the previous input of pipe to a new redirection
 * 
 * @param command command structure
 * @param in_out 0 = IN, 1 = OUT
 */
void	change_input_of_pipe(t_command *command, t_bool in_out)
{
	if (!command || (!command->file_in && in_out == 0) || (!command->file_out
			&& in_out == 1))
		return ;
}
// if (command->fd[in_out] != (int)in_out)
// {
// 	if (close(command->fd[in_out]) != 0)
// 	{
// 		perror("minishell: close");
// 		ft_exit_int(1);
// 	}
// 	if (dup2(command->fd_backup[in_out], command->fd[in_out]) < 0)
// 	{
// 		perror("minishell: dupd");
// 		ft_exit_int(1);
// 	}
// 	command->fd[in_out] = in_out;
// }

// WIP proto to create pipes in command
static int	create_pipe(t_command *command)
{
	if (!command)
		return (1);
	if (command->fd[0] != 0 || command->fd[1] != 1)
	{
		print_fd(2, "minishell: Overwriting fds by pipes\n");
		reset_redirection(command, 0);
		free_garbage();
		exit(EXIT_FAILURE);
	}
	if (pipe(command->pipe_fd) != 0)
	{
		perror("minishell");
		reset_redirection(command, 0);
		free_garbage();
		exit(EXIT_FAILURE);
	}
	command->fd_backup[1] = dup(1);
	command->fd[1] = command->pipe_fd[0];
	dup2(command->fd[1], 1);
	print_fd(1, "creating pipes\n");
	return (0);
}
