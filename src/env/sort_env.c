/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:10:00 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/22 16:30:37 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

void	bubble_sort(t_var **head)
{
	t_var	*current;
	t_bool	swapped;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	swapped = FALSE;
	while (swapped)
	{
		swapped = TRUE;
		current = *head;
		while (current && current->next != NULL)
		{
			if (ft_strcmp(current->value, current->next->value) > 0)
			{
				swap_vars(head, current->value, current->next->value);
				swapped = FALSE;
			}
			current = current->next;
		}
	}
}

void	sort_ascii_order(t_env_vars *env)
{
	t_env_vars	*c_env;

	c_env = copy_env(env);
	if (!c_env)
		return ;
	bubble_sort(&c_env->head_var);
	print_export(c_env);
	free_env(c_env);
}
