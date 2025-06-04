/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_of_last_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:53:26 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/04 16:07:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"

int	ret_of_last_command(t_data *data);

/**
 * @brief Retrieve the return value of the last command structure
 * 
 * @param data data structure
 * @return int 
 */
int	ret_of_last_command(t_data *data)
{
	t_command	*current;

	if (!data || !data->command)
		return (-400);
	current = data->command;
	while (current)
	{
		if (!current->next)
			return (current->return_value);
		current = current->next;
	}
	return (-400);
}
