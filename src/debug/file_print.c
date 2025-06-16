/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:29:35 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/16 17:28:52 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "minishell.h"
#include "ft_printf.h"

void	print_list_files(t_command *command);
void	print_perm_files(t_command *command);

/**
 * @brief Print the list of files in the command structure
 *
 * @param command command structure
 */
void	print_list_files(t_command *command)
{
	t_file		*file;
	t_command	*current;

	current = command;
	while (current)
	{
		file = current->file_in;
		ft_dprintf(2, "tak %p\n", (void *)current);
		while (file != NULL)
		{
			ft_printf("file_in %s\n", file->name);
			file = file->next;
		}
		file = current->file_out;
		while (file != NULL)
		{
			ft_printf("file_out %s\n", file->name);
			file = file->next;
		}
		current = current->next;
	}
}

/**
 * @brief Print the list of permissions of files in the command structure
 *
 * @param command command structure
 */
void	print_perm_files(t_command *command)
{
	t_file	*file;

	file = command->file_in;
	while (file != NULL)
	{
		ft_printf("file_in ");
		if (file->name != NULL)
			ft_printf("%s\n", file->name);
		ft_printf("\thave r:%u w:%u e:%u\n", file->perm_read, file->perm_write,
			file->exist);
		file = file->next;
	}
	file = command->file_out;
	while (file != NULL)
	{
		ft_printf("file_in ");
		if (file->name != NULL)
			ft_printf("%s\n", file->name);
		ft_printf("\thave r:%u w:%u e:%u\n", file->perm_read, file->perm_write,
			file->exist);
		file = file->next;
	}
}
