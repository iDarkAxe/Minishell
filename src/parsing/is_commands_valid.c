/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_commands_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:44:45 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/04 12:20:47 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if all commands are valid or not
 *
 * @param data data structure
 * @return t_bool 1 if valid, 0 otherwise
 */
t_bool	is_commands_valid(t_data *data)
{
	t_command	*current;
	t_bool		error;

	if (!data || !data->command)
		return (0);
	error = 0;
	current = data->command;
	while (current && error == 0)
	{
		if (current->parse_error == 1 || current->file_error == 1
			|| current->return_value != 0)
			error = 1;
		if (error == 1 || !current->tokens || ((ft_strncmp(current->tokens->str,
						"|", 2) == 0 && (!current->tokens->next
						|| !current->tokens->next->str))))
			error = 1;
		current = current->next;
	}
	if (error == 1)
		return (0);
	return (1);
}

// Examples of rejections
/*
finis par |
finis par :
verifier touts les etats (parse error ou file error)
*/
