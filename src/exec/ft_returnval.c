/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_returnval.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:41:27 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/29 17:14:20 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/*
Return_Value utilize a static variable to store the return value
in an integer, but the value range is limited to 0-255, the other value exists
for specific cases.
*/

/**
 * @brief Get the return value object
 * 
 * @return int* pointer to the return value
 */
int	*get_return_value(void)
{
	static int	return_value = 0;

	return (&return_value);
}

/**
 * @brief Set the return value object
 * 
 * @param value new value to set
 * @return int the value set
 */
int	set_return_value(int value)
{
	int	*return_value;

	return_value = get_return_value();
	if (return_value == NULL)
	{
		print_fd(2, "Error of reading return value, exiting.\n");
		ft_exit((char *[]){"1", NULL});
	}
	*return_value = value;
	return (value);
}
