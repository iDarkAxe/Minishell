/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:10:00 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 15:18:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

/**
 * @brief bubble_sort sort algorithm, 
 * check all elements one by one to sort in descending order
 * @param head reference of the head of the environment
 */
static void	bubble_sort(t_garbage *garbage, t_var **head)
{
	t_var	*current;
	t_bool	swapped;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	swapped = TRUE;
	while (swapped == TRUE)
	{
		swapped = FALSE;
		current = *head;
		while (current && current->next != NULL)
		{
			if (ft_strcmp(current->value, current->next->value) > 0)
			{
				swap_vars(garbage, head, current->value, current->next->value);
				swapped = TRUE;
			}
			current = current->next;
		}
	}
}

/**
 * @brief sort_ascii_order sort in ascii order with a bubble sort and print  
 * @param env environment shell 
 */
void	sort_ascii_order(t_garbage *garbage, t_env_vars *env)
{
	t_env_vars	*c_env;

	c_env = copy_env(garbage, env);
	if (!c_env)
		return ;
	bubble_sort(garbage, &c_env->head_var);
	print_export(c_env);
	free_env(garbage, c_env);
}
