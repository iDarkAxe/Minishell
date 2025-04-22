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
#include <string.h>

t_env_vars	sort_ascii_env(t_env_vars env)
{
	t_env_vars	sort_ascii_env;
	t_var		*temp;
	t_var		*var;

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
