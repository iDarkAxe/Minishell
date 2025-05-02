/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:07 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/02 14:51:58 by ppontet          ###   ########lyon.fr   */
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
void	free_pipes(t_command *command, unsigned char i)
{
	int	ret[3];

	if (!command || i >= 1)
		return ;
	if (command->fd[i] != 0)
	{
		ret[0] = close(command->fd[i]);
		if (ret[0] != 0)
			perror("minishell");
		ret[1] = dup2(command->fd_backup[i], i);
		if (ret[1] != 0)
			perror("minishell");
		ret[2] = close(command->fd_backup[i]);
		if (ret[2] != 0)
			perror("minishell");
		if (ret[0] == -1 || ret[1] == -1 || ret[2] == -1)
		{
			print_fd(1, "minishell: error on close or dup2\n");
			ft_exit_int(1);
		}
	}
	free_pipes(command, i + 1);
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
