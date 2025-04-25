/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:10:00 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/18 11:52:50 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

void	bubble_sort(t_var *head)
{
	t_var	*current;
	int		swapped;

	if (head == NULL || head->next == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = head;
		while (current->next != NULL)
		{
			if (ft_strcmp(current->value, current->next->value) > 0)
			{
				swap_vars(head, current->value, current->next->value);
				swapped = 1;
			}
			current = current->next;
		}
	}
}

void	sort_ascii_order(t_env_vars *env)
{
	bubble_sort(env->head_var);
}
