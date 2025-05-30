/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:47:08 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/30 11:27:32 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strndup_gb(t_garbage *garbage, const char *source, size_t len);

/**
 * @brief Create a copy of source into a new pointer
 *	NEEDS to be freed

 * @param garbage garbage structure
 * @param source string to copy
 * @return char* pointer to the new string
 */
char	*ft_strdup_gb(t_garbage *garbage, const char *source)
{
	char	*pointer;
	size_t	count;
	size_t	index;

	count = ft_strlen(source);
	pointer = malloc_gb(garbage, sizeof(char) * (count + 1));
	if (pointer == NULL)
		return (NULL);
	index = 0;
	while (source != NULL && source[index] != '\0' && count > 0)
	{
		pointer[index] = source[index];
		index++;
		count--;
	}
	pointer[index] = '\0';
	return (pointer);
}

/**
 * @brief Create a copy of source into a new pointer of size len
 *	NEEDS to be freed

 * @param garbage garbage structure
 * @param source string to copy
 * @param len size of the new string
 * @return char* pointer to the new string
 */
char	*ft_strndup_gb(t_garbage *garbage, const char *source, size_t len)
{
	char	*pointer;
	size_t	index;

	pointer = malloc_gb(garbage, sizeof(char) * (len + 1));
	if (pointer == NULL)
		return (NULL);
	index = 0;
	while (index < len)
	{
		pointer[index] = source[index];
		index++;
	}
	pointer[len] = '\0';
	return (pointer);
}

/**
 * @brief Free an element in the garbage collector
 *
 * @param garbage garbage structure
 * @param ptr element to free
 */
void	free_element_gb(t_garbage *garbage, void *ptr)
{
	t_element	*element;
	t_element	*previous;

	if (!garbage)
		return ;
	element = garbage->head;
	previous = NULL;
	while (element != NULL)
	{
		if (element->ptr == ptr)
		{
			free(element->ptr);
			element->ptr = NULL;
			if (previous == NULL)
				garbage->head = garbage->head->next;
			else
				previous->next = element->next;
			free(element);
			element = NULL;
			ptr = NULL;
			return ;
		}
		previous = element;
		element = element->next;
	}
}

/**
 * @brief Print the garbage collector
 *
 */
void	print_garbage(t_garbage *garbage)
{
	t_element	*element;

	element = garbage->head;
	while (element != NULL)
	{
		ft_printf("Element %p has ptr : %p\n", (void *)element, element->ptr);
		element = element->next;
	}
}
