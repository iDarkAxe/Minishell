/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:42:42 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/05 16:29:16 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"

int	build_file_access(t_file *file)
{
	if (file == NULL || file->name == NULL)
		return (0);
	if (access(file->name, F_OK) == 0)
		file->exist = 1;
	else
		file->exist = 0;
	if (file->exist == 0)
		return (0);
	if (access(file->name, R_OK) == 0)
		file->perm_read = 1;
	else
		file->perm_read = 0;
	if (access(file->name, W_OK) == 0)
		file->perm_write = 1;
	else
		file->perm_write = 0;
	return (0);
}

char	*ft_trim_word(char *str)
{
	size_t	index;
	size_t	start;
	char	*new_str;

	start = 0;
	while (str[start] != '\0' && ft_isspace(str[start]))
		start++;
	index = 0;
	while (str[start + index] != '\0' && ft_isspace(str[start + index]) == 0)
		index++;
	new_str = ft_strndup(&str[start], index);
	if (new_str == NULL)
		return (str);
	add_to_garbage(new_str);
	free_element_gb(str);
	return (new_str);
}

/**
 * @brief
 *
 * @param file
 * @return int 0 OK, 1 error
 */
int	build_files_data(t_command *command)
{
	t_file	*file;

	if (command == NULL)
		return (0);
	file = command->file_in;
	while (file != NULL)
	{
		file->name = ft_trim_word(file->name);
		build_file_access(file);
		file = file->next;
	}
	file = command->file_out;
	while (file != NULL)
	{
		file->name = ft_trim_word(file->name);
		build_file_access(file);
		file = file->next;
	}
	return (0);
}

/**
 * @brief Add a file to the stack given in param
 *
 * @param command
 * @param index position where a file is detected
 * @param command_file stack to assign a file
 * @return void* NULL if error, command if no stack given,
	and file if all's good
 */
void	*add_file(t_command *command, size_t index, t_file **command_file)
{
	t_file	*file;

	if (command == NULL || command->content == NULL)
		return (NULL);
	if (command_file == NULL)
		return (command);
	file = malloc_gb(sizeof(t_file));
	ft_bzero(file, sizeof(t_file));
	if (file == NULL)
		return (NULL);
	file->name = ft_substr(command->content, index,
			ft_strlen(command->content));
	if (file->name == NULL)
	{
		free_element_gb(file);
		return (NULL);
	}
	add_to_garbage(file->name);
	build_file_access(file);
	file->parsed = 0;
	if (command_file != NULL)
		file->next = *command_file;
	*command_file = file;
	return (file);
}

/**
 * @brief Adds files to the file redirection structure
 *
 * @param command
 * @return int
 */
int	build_files_redirection(t_command *command)
{
	size_t	index;
	t_file	**file;

	if (command == NULL || command->content == NULL)
		return (1);
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
