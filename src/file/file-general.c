/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file-general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:32:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/27 11:17:02 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "garbage.h"
#include "minishell.h"
#include <stdlib.h>

/**
 * @brief Executes all the files redirection tests 
 * 
 * @param command command structure
 * @return int 0 OK, 1 is at least one file redirection is invalid 
 */
int	files_management(t_command *command)
{
	if (build_files_redirection(command) != 0)
	{
		print_fd(2, "Error creating file structure\n");
		ft_exit((char *[]){"1", NULL});
	}
	build_files_data(command);
	if (fill_heredocs(command) != 0)
	{
		print_fd(2, "Error during heredoc creation\n");
		ft_exit((char *[]){"1", NULL});
	}
	if (remove_used_file_tokens(command) == NULL)
	{
		free_garbage();
		print_fd(2, "Error removing file tokens\n");
		ft_exit((char *[]){"1", NULL});
	}
	if (verify_access(command) != 0)
	{
		free_command(command);
		return (1);
	}
	return (0);
}
