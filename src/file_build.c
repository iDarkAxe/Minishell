/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:06:09 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/09 15:13:31 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"

// FIXME Ne fonctionne pas lorsqu'on met plusieurs '<' ou '>'
/**
 * @brief Adds files to the file redirection structure
 *
 * @param command command structure
 * @return int 0, OK, -1 error
 */
int	build_files_redirection(t_command *command)
{
	unsigned int	index;
	t_file			**file;

	if (command == NULL || command->content == NULL)
		return (-1);
	if (ft_strchr(command->content, '<') == NULL && ft_strchr(command->content,
			'>') == NULL)
		return (0);
	index = 0;
	while (command->content[index] != '\0')
	{
		if (command->content[index] == '<')
			file = &command->file_in;
		else if (command->content[index] == '>')
			file = &command->file_out;
		else
			file = NULL;
		if (add_file(command, index + 1, file) == NULL)
			return (1);
		index++;
	}
	return (0);
}

/**
 * @brief Build the data around the files
 *
 * @param command file structure
 * @return int 0 OK, 1 error
 */
int	build_files_data(t_command *command)
{
	t_file	*file;

	if (command == NULL)
		return (0);
	file = command->file_in;
	while (file != NULL)
		file = file_parser(file)->next;
	file = command->file_out;
	while (file != NULL)
		file = file_parser(file)->next;
	return (0);
}
