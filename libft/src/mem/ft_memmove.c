/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:19:49 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 12:41:23 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *destination, const void *source, size_t size);

/**
 * @brief Moves the memory blocks avoiding overlapping, until size blocks
 *
 * @param destination destination memory block
 * @param source source memory block
 * @param size size of the memory block
 * @return void* pointer to the destination memory block
 */
void	*ft_memmove(void *destination, const void *source, size_t size)
{
	unsigned char		*dest_pointer;
	const unsigned char	*src_pointer;

	dest_pointer = (unsigned char *)destination;
	src_pointer = (const unsigned char *)source;
	if (dest_pointer == NULL && src_pointer == NULL)
		return (NULL);
	if (dest_pointer > src_pointer && dest_pointer < (src_pointer + size))
	{
		dest_pointer += size;
		src_pointer += size;
		while (size-- > 0)
			*(--dest_pointer) = *(--src_pointer);
	}
	else
	{
		while (size-- > 0)
			*(dest_pointer++) = *(src_pointer++);
	}
	return ((unsigned char *)destination);
}
