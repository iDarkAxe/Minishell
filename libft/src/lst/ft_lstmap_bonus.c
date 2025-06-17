/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:07:33 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/17 19:07:19 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*element_content_failed(t_list *list_start,
					void (*del)(void *));
static t_list	*element_failed(t_list *list_start,
					void *element_content, void (*del)(void *));

/**
 * @brief Iterated on the linked list 'list' and apply the function 'f'
 * on the content of each element. Create a new list resulting 
 * from the successive applications of 'f'. 
 * The function 'del' is there to destroy the content of an element if
 * necessary.
 *
 * @param lst head of the linked list
 * @param f function to apply to the content of each element
 * @param del function to apply to delete all the content of the element
 * @return t_list* new list modified by f
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list_start;
	t_list	*element;
	void	*element_content;

	if (lst == NULL || f == NULL)
		return (NULL);
	list_start = NULL;
	while (lst != NULL)
	{
		element_content = (*f)(lst->content);
		if (element_content == NULL)
			return (element_content_failed(list_start, del));
		element = ft_lstnew(element_content);
		if (element == NULL)
			return (element_failed(list_start, element_content, del));
		ft_lstadd_back(&list_start, element);
		lst = lst->next;
	}
	return (list_start);
}

/**
 * @brief Verify if element_content assignment has failed,
	and clear list if failed
 *
 * @param list_start list to clear
 * @param del function to apply to delete all the content of the element
 * @return t_list* NULL
 */
static t_list	*element_content_failed(t_list *list_start,
		void (*del)(void *))
{
	ft_lstclear(&list_start, del);
	return (NULL);
}

/**
 * @brief Verify if element assignment has failed, and clear list if failed
 *
 * @param list_start list to clear
 * @param element_content element content to free
 * @param del function to apply to delete all the content of the element
 * @return t_list* NULL
 */
static t_list	*element_failed(t_list *list_start,
		void *element_content, void (*del)(void *))
{
	(*del)(element_content);
	ft_lstclear(&list_start, del);
	return (NULL);
}
