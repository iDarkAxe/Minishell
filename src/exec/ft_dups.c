/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:07 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/01 16:44:58 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "file.h"

static int	create_pipe(t_command *command);

// WIP try to handle redirection and pipes
int	handle_redirections(t_command *command)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (1);
	if (command->next && command->next->tokens
		&& ft_strncmp(command->next->tokens->str, "|", 2) == 0)
		create_pipe(command);
	if (command->file_in || command->file_out)
		read_write_to(command, 0);
	return (0);
}

// TODO PROTECT and secure dup2 and closes
void	free_pipes(t_command *command)
{
	if (!command || !command->tokens || !command->tokens->str)
		return ;
	if (command->fd[0] != 0)
	{
		close(command->fd[0]);
		dup2(command->fd_backup[0], STDIN_FILENO);
		close(command->fd_backup[0]);
	}
	if (command->fd[1] != 1)
	{
		close(command->fd[1]);
		dup2(command->fd_backup[1], STDOUT_FILENO);
		close(command->fd_backup[1]);
	}
	print_fd(1, "free pipes\n");
}

// WIP proto to create pipes in command
static int	create_pipe(t_command *command)
{
	if (!command || (!command->file_in && !command->file_out))
		return (1);
	print_fd(1, "creating pipes\n");
	return (0);
}
