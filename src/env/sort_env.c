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

t_var	*pick_good_var(t_var *head, int i)
{
	t_var	*temp;
	
	temp = head;
	if (!head)
		return (NULL);
	while (i != 0 && temp != NULL)
	{
		i--;
		temp = temp->next;
		if (!temp)
			return (NULL);
	}
	return (temp);
}

int	partition(t_env_vars *env, int low, int high)
{
	t_var	*pivot;
	t_var	*var;
	t_var	*head;
	t_var	*element;
	t_var	*element_1;
	int	i;
	int	j;

	i = low - 1;
	j = low;
	head = env->head_var;
	pivot = pick_good_var(head, high);
	if (!pivot)
		return (-10);
	var = env->head_var;
	element = NULL;
	element_1 = NULL;
	while (j <= high)
	{
		element_1 = pick_good_var(head, j);
		if (!element_1)
			return (-10);
		if (ft_strcmp(element_1->value, pivot->value) < 0)
		{
			i++;
			element = pick_good_var(head, i);
			if (!element)
				return (-10);
			swap_vars(head, element->value, element_1->value);
			var = var->next;
		}
		j++;
	}
	element = pick_good_var(head, i + 1);
	if (!element)
		return (-10);
	element_1 = pick_good_var(head, high);
	if (!element_1)
		return (-10);
	swap_vars(head, element->value, element_1->value);
	return (i + 1);
}

void	quicksort(t_env_vars *env, int low, int high)
{
	int	pivot_index;

	pivot_index = 0;
	if (low < high)
	{
		pivot_index = partition(env, low, high);
		printf("%d", pivot_index);
		if (pivot_index == -10)
			return ;
		quicksort(env, low, pivot_index - 1);
		quicksort(env, pivot_index + 1, high);
	}
}

void	sort_ascii_order(t_env_vars *env)
{
	int	low;
	int	high;

	low = 0;
	high = count_env(*env) - 1;
	printf("HIGH : %d\n", high);
	quicksort(env, low, high);
}
