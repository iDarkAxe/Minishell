/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:29:02 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 13:06:33 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

void	*ft_memset(void *pointer, int value, size_t count);

/**
 * @brief Set a memory zone with a value, count times
 *
 * @param pointer memory zone to set
 * @param value value to set
 * @param count number of times to set the value
 * @return void* pointer to the memory zone
 */
void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*new_pointer;
	size_t			index;

	new_pointer = (unsigned char *)pointer;
	index = 0;
	while (count > 0)
	{
		new_pointer[index] = (unsigned char)value;
		index++;
		count--;
	}
	return (pointer);
}
