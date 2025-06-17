/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:26:57 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/13 17:28:33 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *destination, const void *source, size_t size);

/**
 * @brief Set a memory zone with a value, count times
 *
 * @param destination memory zone to paste
 * @param source memory zone to copy
 * @param size number of times to set the value
 * @return void* pointer to the memory zone
 */
void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	char		*dest_pointer;
	const char	*src_pointer;
	size_t		index;

	dest_pointer = (char *)destination;
	src_pointer = (const char *)source;
	index = 0;
	if (destination == source)
		return (destination);
	while (size > 0)
	{
		dest_pointer[index] = (char)src_pointer[index];
		index++;
		size--;
	}
	return (destination);
}
