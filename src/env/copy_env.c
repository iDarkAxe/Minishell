/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>        +  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:41:13 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/23 12:04:48 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "garbage.h"
#include <stdlib.h>

static void	copy_param(t_garbage *garbage, t_var *var_to_fill,
		const t_var *content)
{
	t_params	*new_node;
	t_params	*temp;

	new_node = NULL;
	temp = content->head_params;
	while (temp != NULL)
	{
		new_node = malloc_gb(garbage, sizeof(t_params));
		if (!new_node)
			return ;
		new_node->next = NULL;
		new_node->value = ft_strdup_gb(garbage, temp->value);
		if (!new_node->value)
		{
			free_element_gb(garbage, new_node);
			return ;
		}
		ft_paramsadd_back(&var_to_fill->head_params, new_node);
		temp = temp->next;
	}
}

void static	free_all_and_exit(t_garbage *garbage, t_env_vars *env,
		t_env_vars *c_env)
{
	free_env(garbage, env);
	free_env(garbage, c_env);
	ft_exit_int(garbage, -1);
}

t_env_vars	*copy_env(t_garbage *garbage, t_env_vars *env)
{
	t_env_vars	*copy_env;
	t_var		*temp;
	t_var		*new_node;

	if (!env)
		return (NULL);
	temp = env->head_var;
	copy_env = malloc_gb(garbage, sizeof(t_env_vars));
	if (!copy_env)
		return (NULL);
	copy_env->head_var = NULL;
	while (temp)
	{
		new_node = get_var(garbage, temp->value);
		if (!new_node || !new_node->value)
			free_all_and_exit(garbage, env, copy_env);
		if (temp->head_params)
			copy_param(garbage, new_node, temp);
		ft_varsadd_back(&copy_env->head_var, new_node);
		temp = temp->next;
	}
	return (copy_env);
}
