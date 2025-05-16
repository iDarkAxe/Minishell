/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_verify_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:59:58 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/11 13:52:15 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "file.h"
#include "garbage.h"
#include "minishell.h"
#include <fcntl.h>

static int	handle_files(t_command *command);
static int	file_permission_check(t_file *file, t_bool in_out);
static int	file_permission_check_outfile(t_file *file, t_bool in_out);

/**
 * @brief Return the last file that is not already_searched
 *
 * @param file file structure
 * @param already_searched previous file from search
 * @return t_file* last file begore already_searched
 */
t_file	*search_last_file(t_file *file, t_file *already_searched)
{
	t_file	*temp;
	t_file	*prev;

	if (file == NULL)
		return (NULL);
	temp = file;
	prev = NULL;
	while (temp != NULL && temp != already_searched)
	{
		prev = temp;
		temp = temp->next;
	}
	if (file->next == NULL || (prev != NULL && prev->next == already_searched))
		return (prev);
	return (NULL);
}

/**
 * @brief Print the right permission error
 *
 * @param in_out 0 = IN, 1 = OUT
 */
static int	file_permission_check(t_file *file, t_bool in_out)
{
	if (file == NULL)
		return (0);
	if (in_out == 0 && file->is_heredoc == 1)
	{
		free_element_gb(file->name);
		file->name = file->tmp->name;
		return (0);
	}
	if (in_out == 0 && file->exist != 1)
	{
		print_fd(2, "minishell: ");
		print_fd(2, file->name);
		print_fd(2, ": No such file or directory\n");
		return (1);
	}
	if ((in_out == 0 && file->perm_read != 1) || (in_out == 1
			&& file->exist == 1 && file->perm_write != 1))
	{
		print_fd(2, "minishell: ");
		print_fd(2, file->name);
		print_fd(2, ": Permission denied\n");
		return (1);
	}
	return (file_permission_check_outfile(file, in_out));
}

/**
 * @brief Create output file if it don't exist,
 * Truncate it's content or append in it's context
 * Always return 0 if it's a infile
 *
 * @param file file structure
 * @param in_out 0 = IN, 1 = OUT
 * @return int 0 OK, 1 error
 */
static int	file_permission_check_outfile(t_file *file, t_bool in_out)
{
	int	fd;

	if (!file || !file->name)
		return (1);
	if (in_out == 0)
		return (0);
	if (file->is_append == 1)
		fd = open(file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell: open");
		ft_exit_int_np(1);
	}
	if (close(fd) != 0)
	{
		perror("minishell: close");
		ft_exit_int_np(1);
	}
	return (0);
}

/**
 * @brief Check that all files have the correct permissions
 * if they are IN (simple or heredoc) or OUT (create/trunc or append)
 *
 * @param command command structure
 * @return int
 */
static int	handle_files(t_command *command)
{
	t_file	*cur_file;
	t_file	*last_file;

	last_file = NULL;
	cur_file = command->file_in;
	while (cur_file != NULL)
	{
		cur_file = search_last_file(command->file_in, last_file);
		last_file = cur_file;
		if (file_permission_check(cur_file, 0) != 0)
			return (1);
	}
	last_file = NULL;
	cur_file = command->file_out;
	while (cur_file != NULL)
	{
		cur_file = search_last_file(command->file_out, last_file);
		last_file = cur_file;
		if (file_permission_check(cur_file, 1) != 0)
			return (1);
	}
	return (0);
}

/**
 * @brief Verify that all files are valid
 * if at least one file is invalid, modifies the boolean in command
 * but still return 0
 *
 * @param command command structure
 * @return int 0 OK, error otherwise
 */
int	verify_access(t_command *command)
{
	t_command	*current;
	int			error_value;

	if (command == NULL)
		return (2);
	current = command;
	while (current != NULL)
	{
		error_value = handle_files(current);
		if (error_value != 0)
			current->file_error = 1;
		current = current->next;
	}
	return (0);
}
