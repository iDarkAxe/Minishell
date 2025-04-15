/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:06:09 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/15 17:23:21 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>

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
	while (command != NULL)
	{
		token = current->tokens;
		while (token != NULL)
		{
			if (ft_strncmp(token->str, "<", 1) == 0)
				file = &command->file_in;
			else if (ft_strncmp(token->str, ">", 1) == 0)
				file = &command->file_out;
			else
				file = NULL;
			if (add_file(command, token, file) == NULL)
				return (1);
			token = token->next;
		}
		command = command->next;
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

char	*read_heredoc(t_tmp *tmp, char *delimiteur)
{
	char	*str;

	while (1)
	{
		str = readline("heredoc> ");
		if (str == NULL)
			return (NULL);
		if (ft_strncmp(str, delimiteur, ft_strlen(delimiteur) + 1) == 0)
			break ;
		write(tmp->fd, str, ft_strlen(str));
		free(str);
		str = NULL;
		write(tmp->fd, "\n", 1);
	}
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (close(tmp->fd) == -1)
	{
		write(2, "Error closing heredoc file\n", 28);
		return (NULL);
	}
	return (tmp->name);
}
