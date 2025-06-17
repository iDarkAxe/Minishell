/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:55:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/17 18:06:48 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Allocate (with malloc(3)) and return a new element.
 * The variable member 'content' is initialized with the value
 * of the parameter 'content'.
 * The variable 'next' is initialized to NULL.
 * 
 * @param content content to add to the new element
 * @return t_list* new element
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (element == NULL)
		return (NULL);
	if (content == NULL)
		element->content = NULL;
	else
		element->content = content;
	element->next = NULL;
	return (element);
}
