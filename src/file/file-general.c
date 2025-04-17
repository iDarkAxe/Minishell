/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file-general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:32:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/17 16:35:20 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "garbage.h"
#include "file.h"
#include <stdlib.h>

void	files_management(t_command *command)
{
	if (build_files_redirection(command) != 0)
	{
		free_garbage();
		print_fd(2, "Error creating file structure\n");
		ft_exit((char *[]){"1", NULL});
	}
	if (build_files_data(command) != 0)
	{
		free_garbage();
		print_fd(2, "Error creating file data\n");
		ft_exit((char *[]){"1", NULL});
	}
	if (remove_used_file_tokens(command) == NULL)
	{
		free_garbage();
		print_fd(2, "Error removing file tokens\n");
		ft_exit((char *[]){"1", NULL});
	}
}
