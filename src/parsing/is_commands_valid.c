/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_commands_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:44:45 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/04 19:36:23 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_command_valid_other_option(t_data *data, t_command *command,
					t_bool *error);

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
		{
			data->ret = 2;
			return (0);
		}
		if (is_command_valid_other_option(data, current, &error) == 1)
			return (0);
		current = current->next;
	}
	if (error == 1)
		return (0);
	return (1);
}

t_bool	is_command_valid_other_option(t_data *data, t_command *command,
		t_bool *error)
{
	if (!data || !command || !error)
		return (1);
	if (!command->tokens || ((ft_strncmp(command->tokens->str, "|", 2) == 0
				&& (!command->tokens->next || !command->tokens->next->str))))
	{
		*error = 1;
		data->ret = 127;
		return (1);
	}
	return (0);
}

// Examples of rejections
/*
finis par |
finis par :
verifier touts les etats (parse error ou file error)
*/
