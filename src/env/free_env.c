/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:12:06 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/05 15:57:58 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"

void	free_params(t_params *element)
{
	t_params	*temp;

	if (!element)
		return ;
	temp = NULL;
	while (element)
	{
		temp = element->next;
		free_element_gb(element->value);
		free_element_gb(element);
		element = temp;
	}
	return ;
}

void	free_env(t_env_vars *env)
{
	t_var	*temp;

	if (!env)
		return ;
	temp = NULL;
	while (env->head_var)
	{
		temp = env->head_var->next;
		free_params(env->head_var->head_params);
		free_element_gb(env->head_var->value);
		free_element_gb(env->head_var);
		env->head_var = temp;
	}
}
