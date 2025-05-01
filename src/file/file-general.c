/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file-general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:32:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/01 16:48:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "garbage.h"
#include "minishell.h"
#include <stdlib.h>
#include "fcntl.h"

/**
 * @brief Executes all the files redirection tests 
 * 
 * @param command command structure
 * @return int 0 OK, 1 is at least one file redirection is invalid 
 */
int	files_management(t_command *command)
{
	if (build_files_redirection(command) != 0)
	{
		print_fd(2, "Error creating file structure\n");
		ft_exit_int(1);
	}
	build_files_data(command);
	if (fill_heredocs(command) != 0)
	{
		print_fd(2, "Error during heredoc creation\n");
		ft_exit_int(1);
	}
	if (remove_used_file_tokens(command) == NULL)
	{
		free_garbage();
		print_fd(2, "Error removing file tokens\n");
		ft_exit_int(1);
	}
	if (verify_access(command) != 0)
	{
		free_command(command);
		return (1);
	}
	return (0);
}

// WIP open file
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
		fd = open(file->name, O_WRONLY | O_TRUNC);
	else
		fd = open(file->name, O_WRONLY | O_APPEND);
	if (fd < 0)
	{
		perror("minishell");
		ft_exit_int(EXIT_FAILURE);
	}
	return (fd);
}

// WIP prototype to files
void	read_write_to(t_command *command, unsigned char nbr)
{
	t_file	*temp;

	if (!command || (!command->file_in && !command->file_out) || nbr > 2)
		return ;
	if (nbr == 0)
		temp = command->file_in;
	else
		temp = command->file_out;
	if (nbr == 2 || !temp)
	{
		read_write_to(command, nbr + 1);
		return ;
	}
	command->fd_backup[nbr] = dup(nbr);
	if (command->fd_backup[nbr] < 0)
	{
		perror("minishell");
		ft_exit_int(EXIT_FAILURE);
	}
	command->fd[nbr] = open_file_with_rights(temp, nbr);
	if (dup2(command->fd[nbr], nbr) == -1)
	{
		perror("minishell");
		ft_exit_int(EXIT_FAILURE);
	}
}
