/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:07:07 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/15 11:46:03 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *src, const void *set, size_t size);

/**
 * @brief Compares the first size bytes of the memory areas src and set.
 *
 * @param src source memory block
 * @param set set memory block
 * @param size size of the memory block
 * @return int difference between the first different byte
 */
int	ft_memcmp(const void *src, const void *set, size_t size)
{
	size_t				index;
	const unsigned char	*src_pointer;
	const unsigned char	*set_pointer;

	index = 0;
	src_pointer = (const unsigned char *)src;
	set_pointer = (const unsigned char *)set;
	if (size == 0)
		return (0);
	while (index < (size - 1) && src_pointer[index] == set_pointer[index])
		index++;
	return ((unsigned char)src_pointer[index]
		- (unsigned char)set_pointer[index]);
}
