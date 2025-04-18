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
#include <string.h>

t_env_vars	sort_ascii_env(t_env_vars env) 
{
	t_env_vars	sort_ascii_env;
	t_var	*temp;
	t_var	*var;

	var = env.head_var;
	while (var)
	{
		if (strcmp(var->value, var->next->value) > 0)
		{
			temp = var;
			var = temp->next;
			temp->next = temp;
		}
	}
	return (sort_ascii_env);
}
