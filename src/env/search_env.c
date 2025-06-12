/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>        +  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:53:17 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/05 12:14:42 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"

t_var	*search_env_var(t_env_vars *env, char *var)
{
	t_var	*head;

	head = env->head_var;
	while (head != NULL)
	{
		if (ft_strcmp(head->value, var) == 0)
			return (head);
		head = head->next;
	}
	if (head == NULL)
		return (NULL);
	return (NULL);
}
