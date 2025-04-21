/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_verify_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:59:58 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/21 13:59:33 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "minishell.h"

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
	if ( file->next == NULL || (prev != NULL && prev->next == already_searched))
		return (prev);
	return (NULL);
}

/**
 * @brief Print the right permission error 
 *
 * @param in_out 1 = IN, 0 = OUT
 */
int	file_permission_check(t_file *file, t_bool in_out)
{
	if (file == NULL)
		return (0);
	if (in_out == 1 && file->exist != 1)
	{
		print_fd(2, "minishell: ");
		print_fd(2, file->name);
		print_fd(2, ": No such file or directory\n");
		return (1);
	}
	if ((in_out == 1 && file->perm_read != 1) || (in_out == 0
			&& file->exist == 1 && file->perm_write != 1))
	{
		print_fd(2, "minishell: ");
		print_fd(2, file->name);
		print_fd(2, ": Permission denied\n");
		return (1);
	}
	return (0);
}

int	handle_file(t_command *command)
{
	t_file	*cur_file;
	t_file *last_file;

	last_file = NULL;
	cur_file = command->file_in;
	while (cur_file != NULL)
	{
		cur_file = search_last_file(command->file_in, last_file);
		last_file = cur_file;
		if (file_permission_check(cur_file, 1) != 0)
			return (1);
	}
	last_file = NULL;
	cur_file = command->file_out;
	while (cur_file != NULL)
	{
		cur_file = search_last_file(command->file_in, last_file);
		last_file = cur_file;
		if (file_permission_check(cur_file, 0) != 0)
			return (1);
	}
	return (0);
}

#include <stdio.h>

int	verify_access(t_command *command)
{
	t_command	*current;
	int			error_value;

	if (command == NULL)
		return (2);
	current = command;
	while (current != NULL)
	{
		error_value = handle_file(current);
		if (error_value != 0)
			current->file_error = 1;
		current = current->next;
	}
	return (0);
}
