/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:06:09 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/17 09:08:10 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "file.h"

static int	build_file_data(t_command *command);

/**
 * @brief Adds files to the file redirection structure
 *
 * @param command command structure
 * @return int 0, OK, -1 error
 */
int	build_files_redirection(t_command *command)
{
	t_command	*current;
	t_token		*token;
	t_file		**file;

	if (command == NULL || command->tokens == NULL)
		return (-1);
	current = command;
	while (current != NULL)
	{
		token = current->tokens;
		while (token != NULL && token->str != NULL)
		{
			if (ft_strncmp(token->str, "<", 1) == 0)
				file = &current->file_in;
			else if (ft_strncmp(token->str, ">", 1) == 0)
				file = &current->file_out;
			else
				file = NULL;
			if (add_file(current, token, file) == NULL)
				return (1);
			token = token->next;
		}
		current = current->next;
	}
	return (0);
}

/**
 * @brief Build the data around the files in all commands
 *
 * @param command file structure
 * @return int 0 OK, 1 error
 */
int	build_files_data(t_command *command)
{
	t_command	*current;

	current = command;
	while (current != NULL)
	{
		build_file_data(current);
		current = current->next;
	}
	return (0);
}

/**
 * @brief Build the data around the file in one command
 *
 * @param command file structure
 * @return int 0 OK, 1 error
 */
static int	build_file_data(t_command *command)
{
	t_file	*file;

	if (command == NULL)
		return (1);
	file = command->file_in;
	while (1)
	{
		file = file_parser(file);
		if (file == NULL)
			break ;
		file = file->next;
	}
	file = command->file_out;
	while (1)
	{
		file = file_parser(file);
		if (file == NULL)
			break ;
		file = file->next;
	}
	return (0);
}
