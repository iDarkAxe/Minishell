/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:07 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/07 11:12:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "file.h"
#include "garbage.h"
#include "minishell.h"

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
	command->fd[i] = i;
	command->fd_backup[i] = i;
}
// fd_default(command);

/**
 * @brief Change the previous input of pipe to a new redirection
 *
 * @param command command structure
 * @param in_out 0 = IN, 1 = OUT
 */
/* void	change_input_of_pipe(t_command *command, t_bool in_out)
{
	int	ret[2];

	if (!command || (!command->file_in && in_out == 0) || (!command->file_out
			&& in_out == 1))
		return ;
	ret[0] = close(command->fd[in_out]);
	if (ret[0] != 0)
		perror("minishell: close");
	ret[1] = close(command->fd_backup[in_out]);
	if (ret[1] != 0)
		perror("minishell: close");
	if (ret[0] != 0 || ret[1] != 0)
	{
		reset_redirection(command, 0);
		free_garbage();
		exit(EXIT_FAILURE);
	}
} */

// FIXME Need to add verifications to dup, dup2 and close

int	create_pipe(t_command *command)
{
	if (!command || !command->next)
		return (1);
	if (pipe(command->fd) != 0)
	{
		perror("minishell");
		free_garbage();
		exit(EXIT_FAILURE);
	}
	dup2(command->fd[1], 1);
	command->next->fd[0] = command->fd[0];
	command->fd[0] = 0;
	dup2(command->next->fd[0], 0);
	print_fd(2, "creating pipe\n");
	return (0);
}

/**
 * @brief Prepare the pipes for all the commands,
 * if no pipes are needed, it does nothing
 *
 * @param command command structure
 */
// void	prepare_pipes(t_command *command)
// {
// 	if (!command || !command->tokens || !command->tokens->str || !command->next
// 		|| !command->next->tokens || !command->next->tokens->str)
// 		return ;
// 	if (ft_strncmp(command->next->tokens->str, "|", 2) != 0)
// 		return ;
// 	current = command;
// 	while (current && current->next)
// 	{
// 		printf("pipe ici\n");
// 		create_pipe(current);
// 		current = current->next;
// 	}
// }
