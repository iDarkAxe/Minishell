/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:29:35 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/05 16:29:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_list_files(t_command *command);
void	print_perm_files(t_command *command);

void	print_list_files(t_command *command)
{
	t_file	*file;

	file = command->file_in;
	while (file != NULL)
	{
		printf("file_in %s\n", file->name);
		file = file->next;
	}
	file = command->file_out;
	while (file != NULL)
	{
		printf("file_out %s\n", file->name);
		file = file->next;
	}
}

void	print_perm_files(t_command *command)
{
	t_file	*file;

	file = command->file_in;
	while (file != NULL)
	{
		printf("file_in ");
		if (file->name != NULL)
			printf("%s\n", file->name);
		printf("\thave r:%u w:%u e:%u\n", file->perm_read, file->perm_write,
			file->exist);
		file = file->next;
	}
	file = command->file_out;
	while (file != NULL)
	{
		printf("file_in ");
		if (file->name != NULL)
			printf("%s\n", file->name);
		printf("\thave r:%u w:%u e:%u\n", file->perm_read, file->perm_write,
			file->exist);
		file = file->next;
	}
}
