/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:06:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/15 11:45:56 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

const void	*ft_memchr(const void *memory_block, int searched_char,
				size_t size);

/**
 * @brief Research the first occurence of a value typed int,
 * but interpreted as a char in a memory block.
 *
 * @param memory_block memory block to search in
 * @param searched_char value to search
 * @param size size of the memory block
 * @return void* pointer to the first occurence of the value
 * or NULL if not found
 */
const void	*ft_memchr(const void *memory_block, int searched_char, size_t size)
{
	const unsigned char	*pointer;
	size_t				index;

	pointer = (const unsigned char *)memory_block;
	index = 0;
	while (index < size)
	{
		if (pointer[index] == (unsigned char)searched_char)
			return ((const void *)&pointer[index]);
		index++;
	}
	return (NULL);
}
