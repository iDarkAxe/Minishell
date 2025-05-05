/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:41:13 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/23 14:41:59 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include <stdlib.h>

static void	copy_param(t_var *temp, const t_var *var)
{
	t_params	*new_param;
	t_params	*temporary;

	new_param = NULL;
	temporary = var->head_params;
	while (temporary)
	{
		new_param = malloc_gb(sizeof(t_params));
		if (!new_param)
			return ;
		new_param->next = NULL;
		new_param->value = ft_strdup_gb(temporary->value);
		if (!new_param->value)
			return ;
		ft_paramsadd_back(&temp->head_params, new_param);
		temporary = temporary->next;
	}
}

t_env_vars	*copy_env(t_env_vars *env)
{
	t_env_vars	*copy_env;
	t_var		*var;
	t_var		*temp;

	var = env->head_var;
	copy_env = malloc_gb(sizeof(t_env_vars));
	if (!copy_env)
		return (NULL);
	copy_env->head_var = NULL;
	while (var)
	{
		temp = malloc_gb(sizeof(t_var));
		if (!temp)
			return (NULL);
		temp->next = NULL;
		temp->value = ft_strdup_gb(var->value);
		if (!temp->value)
			return (NULL);
		temp->head_params = NULL;
		copy_param(temp, var);
		ft_varsadd_back(&copy_env->head_var, temp);
		var = var->next;
	}
	return (copy_env);
}
