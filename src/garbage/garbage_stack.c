/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:08:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 13:17:58 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

/**
 * @brief Allocates and returns the newly created element
 * 'value' is initialised with content
 * 'next' is set to NULL
 *
 * @param ptr pointer to add in the element
 * @return t_element* pointer to the element
 */
t_element	*ft_garbagenew(void *ptr)
{
	t_element	*element;

	element = malloc(sizeof(t_element));
	if (element == NULL)
		return (NULL);
	element->ptr = ptr;
	element->next = NULL;
	return (element);
}

/**
 * @brief Adds the 'new' element at the start of stack
 *
 * @param garbage garbage structure
 * @param new element to add
 */
void	ft_garbageadd_front(t_garbage *garbage, t_element *new)
{
	if (new == NULL)
		return ;
	new->next = garbage->next;
	garbage->next = new;
}

/**
 * @brief Adds the 'new' element at the end of stack
 *
 * @param garbage garbage structure
 * @param new element to add
 */
void	ft_garbageadd_back(t_garbage *garbage, t_element *new)
{
	t_element	*last;

	if (new == NULL)
		return ;
	if (garbage->next == NULL)
	{
		garbage->next = new;
		return ;
	}
	last = garbage->next;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

inline void	ft_garbage_free_element(t_element *element)
{
	free(element->ptr);
	element->ptr = NULL;
}

/**
 * @brief Remove all elements from garbage
 *
 * @param garbage garbage structure
 * @return int 0 OK, -1 is error
 */
int	ft_garbageclear(t_garbage *garbage)
{
	t_element	*element;
	t_element	*temp;

	element = garbage->next;
	while (element != NULL && garbage->n_elements > 0)
	{
		temp = element->next;
		free(element->ptr);
		element->ptr = NULL;
		free(element);
		element = temp;
		garbage->n_elements--;
	}
	garbage->next = NULL;
	return (0);
}
