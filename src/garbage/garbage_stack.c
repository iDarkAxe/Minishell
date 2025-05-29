/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:08:24 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/26 18:03:48 by ppontet          ###   ########lyon.fr   */
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
	new->next = garbage->head;
	garbage->head = new;
}

/**
 * @brief Adds the 'new' element at the end of stack
 * @deprecated not used anywhere as add_front is faster
 *
 * @param garbage garbage structure
 * @param new element to add
 */
__attribute__((deprecated))
void	ft_garbageadd_back(t_garbage *garbage, t_element *new)
{
	t_element	*last;

	if (new == NULL)
		return ;
	if (garbage->head == NULL)
	{
		garbage->head = new;
		return ;
	}
	last = garbage->head;
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

	if (!garbage)
		return (-1);
	element = garbage->head;
	while (element != NULL)
	{
		temp = element->next;
		free(element->ptr);
		element->ptr = NULL;
		free(element);
		element = temp;
		garbage->n_elements--;
	}
	garbage->head = NULL;
	return (0);
}
