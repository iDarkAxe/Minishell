/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:12:12 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 15:19:00 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"

/**
 * @brief Find_str function to find the string of the two t_var to swap
 *
 * @param head reference to the head of the t_vars list to be swapped swap 
 * structure compose of multiple t_var to swap str string 
 * inside t_var str_1 string inside a t_var to exchange with str
 */
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

/**
 * @brief Swap_var swap two t_var
 *
 * @param head reference to the head of the t_vars list 
 * to be swapped swap structure compose of multiple t_var to swap 
 */
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

/**
 * @brief Swap_vars allows swap nodes t_vars
 *
 * @param head reference to the head of the t_vars list to be swapped,
 * str string inside t_var str_1 string inside a t_var to exchange with str
 */
void	swap_vars(t_garbage *garbage, t_var **head, char *str, char *str_1)
{
	t_vars	*swap;

	swap = malloc_gb(garbage, sizeof(t_vars));
	if (!swap || !str || !str_1)
		return ;
	swap->prev_str = NULL;
	swap->prev_str_1 = NULL;
	swap->curr_str = NULL;
	swap->curr_str_1 = NULL;
	swap->temp = NULL;
	swap->curr = *head;
	if (ft_strcmp(str, str_1) == 0)
		return ;
	find_str(swap, head, str, str_1);
	if (swap->curr_str == NULL || swap->curr_str_1 == NULL)
		return ;
	swap_var(head, swap);
	return ;
}
