/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:58:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/13 23:28:56 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Frees multiple pointers
 * 
 * @param ptr Array of pointers
 */
void	ft_frees(void **ptr)
{
	size_t	index;

	if (!ptr)
		return ;
	index = 0;
	while (ptr[index] != NULL)
	{
		free(ptr[index]);
		index++;
	}
	free(ptr);
}
