/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/30 11:25:31 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "garbage.h"
#include "minishell.h"

/**
 * @brief Free array of strings
 *
 * @param garbage garbage structure
 * @param array array of strings
 */
void	free_array(t_garbage *garbage, char **array)
{
	size_t	index;

	if (array == NULL)
		return ;
	index = 0;
	while (array && array[index])
	{
		free_element_gb(garbage, array[index]);
		array[index] = NULL;
		index++;
	}
	free_element_gb(garbage, array);
	array = NULL;
}
