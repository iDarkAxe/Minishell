/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:53:17 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/29 10:34:31 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"

t_var	*search_env_var(t_env_vars *env, char *var)
{
	t_var	*head;
	t_var	*temp;

	head = env->head_var;
	temp = head;
	while (head != NULL)
	{
		if (ft_strcmp(head->value, var) == 0)
		{
			temp = head;
			break ;
		}
		head = head->next;
	}
	if (head == NULL)
		return (NULL);
	return (temp);
}
