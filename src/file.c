/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:42:42 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/04 13:15:34 by ppontet          ###   ########lyon.fr   */
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
 * @brief
 *
 * @param file
 * @return int 0 OK, 1 error
 */
int	build_file_data(t_file *file)
{
	char	*current_path;
	char	*path;

	if (file == NULL || file->name == NULL)
		return (0);
	current_path = "./";
	path = ft_strjoins((char *[]){current_path, file->name, NULL});
	if (path == NULL)
		return (1);
	add_to_garbage(path);
	free_element_gb(file->name);
	file->name = path;
	build_file_access(file);
	free_element_gb(path);
	return (0);
}

int	build_file_redirection(t_command *command)
{
	if (command == NULL)
		return (1);
	if (ft_strchr(command->content, '<') == NULL || ft_strchr(command->content,
			'>') == NULL)
		return (0);
}
