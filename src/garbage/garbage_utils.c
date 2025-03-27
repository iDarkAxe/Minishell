/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:47:08 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/26 14:04:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Create a copy of source into a new pointer
 *	NEEDS to be freed

 * @param source string to copy
 * @return char* pointer to the new string
 */
char	*ft_strdup_gb(const char *source)
{
	char	*pointer;
	size_t	count;
	size_t	index;

	count = ft_strlen(source);
	pointer = malloc_gb(sizeof(char) * (count + 1));
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

 * @param source string to copy
 * @param len size of the new string
 * @return char* pointer to the new string
 */
char	*ft_strndup_gb(const char *source, size_t len)
{
	char	*pointer;
	size_t	index;

	pointer = malloc_gb(sizeof(char) * (len + 1));
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

void	free_element_gb(void *ptr)
{
	t_garbage	*garbage;
	t_element	*element;
	t_element	*previous;

	garbage = get_garbage();
	element = garbage->head;
	previous = NULL;
	while (element != NULL)
	{
		if (element->ptr == ptr)
		{
			free(element->ptr);
			if (previous == NULL)
				garbage->head = garbage->head->next;
			else
				previous->next = element->next;
			free(element);
			return ;
		}
		previous = element;
		element = element->next;
	}
}

void	print_garbage(void)
{
	t_element	*element;

	element = get_garbage()->head;
	while (element != NULL)
	{
		printf("Element %p has ptr : %p\n", element, element->ptr);
		element = element->next;
	}
}
