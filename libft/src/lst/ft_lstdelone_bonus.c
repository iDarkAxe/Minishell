/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:08:51 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/17 18:03:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Free the memory of the element passed as a parameter
 * using the function 'del' and free(3).
 * The memory of next must not be freed.
 * 
 * @param lst head of the linked list
 * @param del function to apply to delete all the content of the element
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	(*del)(lst->content);
	free(lst);
}
