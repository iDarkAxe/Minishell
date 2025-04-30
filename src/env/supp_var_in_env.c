/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_var_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:21:04 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/29 15:51:30 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include <stdlib.h>

void	supp_var(t_var **head, char *str)
{
	t_vars	*supp;

	if (!head || !str)
		return ;
	supp = malloc_gb(sizeof(t_vars));
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
			free_element_gb(supp->curr->value);
			free_element_gb(supp->curr);
			break ;
		}
		supp->prev_str = supp->curr;
		supp->curr = supp->curr->next;
	}
	return ;
}
