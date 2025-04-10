/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:42:42 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/09 16:49:55 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"

/**
 * @brief Build the file using access and check permissions
 *
 * @param file file structure
 * @return int 0, OK, -1 error
 */
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

/**
 * @brief Trim the first word detected and remove all the unnecessary 
 *
 * @param str string to search the word
 * @return char* the word found
 */
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

/* FIXME Parsing à appliquer ici, et ne fonctionne pas pour les here-doc
pour les outfiles en mode append */
/**
 * @brief Parse the file structure
 *
 * @param file file structure
 * @return t_file* file given in paramter
 */
t_file	*file_parser(t_file *file)
{
	if (file == NULL)
		return (NULL);
	file->name = ft_trim_word(file->name);
	build_file_access(file);
	return (file);
}

/**
 * @brief Add a file to the stack given in param
 *
 * @param command command structure
 * @param index position where a file is detected
 * @param command_file stack to assign a file
 * @return void* NULL if error, command if no stack given,
	and file if all's good
 */
void	*add_file(t_command *command, unsigned int index, t_file **command_file)
{
	t_file	*file;

	if (command == NULL || command->content == NULL)
		return (NULL);
	if (command_file == NULL)
		return (command);
	file = malloc_gb(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	ft_bzero(file, sizeof(t_file));
	file->name = ft_substr(command->content, index,
			ft_strlen(command->content));
	if (file->name == NULL)
	{
		free_element_gb(file);
		return (NULL);
	}
	add_to_garbage(file->name);
	file->parsed = 0;
	if (command_file != NULL)
		file->next = *command_file;
	*command_file = file;
	return (file);
}
