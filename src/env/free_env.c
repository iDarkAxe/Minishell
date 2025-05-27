/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:12:06 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/22 16:36:09 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"

void	free_params(t_garbage *garbage, t_params *element)
{
	t_params	*temp;

	if (!element)
		return ;
	temp = NULL;
	while (element)
	{
		temp = element->next;
		free_element_gb(garbage, element->value);
		free_element_gb(garbage, element);
		element = temp;
	}
	return ;
}

void	free_env(t_garbage *garbage, t_env_vars *env)
{
	t_var	*temp;

	if (!env)
		return ;
	temp = NULL;
	while (env->head_var)
	{
		temp = env->head_var->next;
		free_params(garbage, env->head_var->head_params);
		free_element_gb(garbage, env->head_var->value);
		free_element_gb(garbage, env->head_var);
		env->head_var = temp;
	}
}
