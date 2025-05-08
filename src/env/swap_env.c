/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:12:12 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/28 14:54:12 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include <stdio.h>

static void	find_str(t_vars *swap, t_var **head, char *str, char *str_1)
{
	while (swap->curr != NULL)
	{
		if (ft_strcmp(str, swap->curr->value) == 0)
		{
			swap->curr_str = swap->curr;
			break ;
		}
		swap->prev_str = swap->curr;
		swap->curr = swap->curr->next;
	}
	swap->curr = *head;
	while (swap->curr != NULL)
	{
		if (ft_strcmp(str_1, swap->curr->value) == 0)
		{
			swap->curr_str_1 = swap->curr;
			break ;
		}
		swap->prev_str_1 = swap->curr;
		swap->curr = swap->curr->next;
	}
	swap->curr = *head;
}

static void	swap_var(t_var **head, t_vars *swap)
{
	if (swap->prev_str != NULL)
		swap->prev_str->next = swap->curr_str_1;
	else
		*head = swap->curr_str_1;
	if (swap->prev_str_1 != NULL)
		swap->prev_str_1->next = swap->curr_str;
	else
		*head = swap->curr_str;
	swap->temp = swap->curr_str_1->next;
	swap->curr_str_1->next = swap->curr_str->next;
	swap->curr_str->next = swap->temp;
}

void	swap_vars(t_var **head, char *str, char *str_1)
{
	t_vars	*swap;

	swap = malloc_gb(sizeof(t_vars));
	if (!swap || !str || !str_1)
		return ;
	swap->prev_str = NULL;
	swap->prev_str_1 = NULL;
	swap->curr_str = NULL;
	swap->curr_str_1 = NULL;
	swap->curr = *head;
	swap->temp = NULL;
	if (ft_strcmp(str, str_1) == 0)
		return ;
	find_str(swap, head, str, str_1);
	if (swap->curr_str == NULL || swap->curr_str_1 == NULL)
		return ;
	swap_var(head, swap);
	return ;
}
