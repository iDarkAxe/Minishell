/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_var_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:21:04 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/22 17:06:37 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include <stdlib.h>

void	supp_var(t_garbage *garbage, t_var **head, char *str)
{
	t_supp	*supp;

	if (!head || !str)
		return ;
	supp = malloc_gb(garbage, sizeof(t_supp));
	if (!supp)
		return ;
	supp->curr = *head;
	supp->prev_str = NULL;
	while (supp->curr != NULL)
	{
		if (ft_strcmp(supp->curr->value, str) == 0)
		{
			if (supp->prev_str)
				supp->prev_str->next = supp->curr->next;
			else
				*head = supp->curr->next;
			free_params(garbage, supp->curr->head_params);
			free_element_gb(garbage, supp->curr);
			break ;
		}
		supp->prev_str = supp->curr;
		supp->curr = supp->curr->next;
	}
}
