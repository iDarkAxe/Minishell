/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>        +  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:10:00 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/12 17:52:17 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

/**
 * @brief bubble_sort sort algorithm, check all elements one by one to sort in descending order
 * @param head reference of the head of the environment
 * @return
 */
static void	bubble_sort(t_garbage *garbage, t_var **head)
{
	t_var	*current;
	t_bool	swapped;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	swapped = TRUE;
	while (swapped)
	{
		swapped = FALSE;
		current = *head;
		while (current && current->next != NULL)
		{
			if (ft_strcmp(current->value, current->next->value) > 0)
			{
				swap_vars(garbage, head, current->value, current->next->value);
				swapped = FALSE;
			}
			current = current->next;
		}
	}
}

/**
 * @brief sort_ascii_order sort in ascii order with a bubble sort and print  
 * @param env environment shell 
 * @return
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
