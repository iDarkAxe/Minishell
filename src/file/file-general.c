/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file-general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:32:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/09 16:35:45 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "file.h"
#include "garbage.h"

#include <fcntl.h>
#include <stdlib.h>

/**
 * @brief Executes all the files redirection tests
 *
 * @param command command structure
 * @return int 0 OK, 1 is at least one file redirection is invalid
 */
int	files_management(t_command *command)
{
	if (command->parse_error == 1)
		return (1);
	if (build_files_redirection(command) != 0)
	{
		print_fd(2, "minishell: error creating file structure\n");
		ft_exit_int_np(1);
	}
	build_files_data(command);
	if (fill_heredocs(command) != 0)
	{
		print_fd(2, "minishell: error during heredoc creation\n");
		ft_exit_int_np(1);
	}
	if (verify_access(command) != 0)
		return (1);
	if (remove_used_file_tokens(command) == NULL)
	{
		print_fd(2, "minishell: error removing file tokens\n");
		ft_exit_int_np(1);
	}
	return (0);
}

/**
 * @brief Open a file with it's rights (permissions)
 *
 * @param file file structure
 * @param in_out 0 = IN, 1 = OUT
 * @return int
 */
int	open_file_with_rights(t_file *file, t_bool in_out)
{
	int	perms;
	int	fd;

	perms = 0;
	if (file == NULL)
		return (-1);
	if (file->is_heredoc == 1)
		return (file->tmp->fd);
	if (in_out == 0)
		fd = open(file->name, O_RDONLY);
	else if (in_out == 1 && file->is_append == 0)
		fd = open(file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("minishell: open");
		ft_exit_int_np(EXIT_FAILURE);
	}
	return (fd);
}

/**
 * @brief Opens the files to read and writes
 *
 * @param in_out 0 = IN, 1 = OUT
 */
void	read_write_to(t_command *command, t_bool in_out)
{
	if (!command || (!command->file_in && in_out == 0) || (!command->file_out
			&& in_out == 1))
		return ;
	if (in_out == 0)
		command->fd[in_out] = open_file_with_rights(command->file_in, in_out);
	else
		command->fd[in_out] = open_file_with_rights(command->file_out, in_out);
	if (dup2(command->fd[in_out], (int)in_out) == -1)
	{
		perror("minishell");
		command->file_error = 1;
	}
	if (close(command->fd[in_out]) != 0)
	{
		perror("minishell");
		command->file_error = 1;
	}
}

/**
 * @brief Put the fds in command to there default values
 *
 * @param command command structure
 */
void	fd_default(t_command *command)
{
	if (!command)
		return ;
	command->fd[0] = 0;
	command->fd[1] = 1;
	command->fd_backup[0] = 0;
	command->fd_backup[1] = 1;
}
