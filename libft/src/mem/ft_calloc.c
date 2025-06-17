/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:07:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/17 18:09:38 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Allocates a new memory zone, and set all bits to zero
 *
 * @param element_count number of elements
 * @param element_size size of each element
 * @return void* pointer to the new memory zone
 */
void	*ft_calloc(size_t element_count, size_t element_size)
{
	void	*pointer;
	size_t	nbr_element;

	if (element_size == 0 || element_count == 0)
		return (malloc(0));
	if (SIZE_MAX / element_size < element_count || SIZE_MAX
		/ element_count < element_size)
		return (NULL);
	nbr_element = element_size * element_count;
	pointer = malloc(nbr_element);
	if (pointer == NULL)
		return (NULL);
	ft_bzero(pointer, nbr_element);
	return (pointer);
}
