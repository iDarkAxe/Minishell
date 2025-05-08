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

static void	copy_param(t_var *var_to_fill, const t_var *content)
{
	t_params	*new_node;
	t_params	*temp;

	new_node = NULL;
	temp = content->head_params;
	while (temp != NULL)
	{
		new_node = malloc_gb(sizeof(t_params));
		if (!new_node)
			return ;
		new_node->next = NULL;
		new_node->value = ft_strdup_gb(temp->value);
		if (!new_node->value)
		{
			free_element_gb(new_node);
			return ;
		}
		ft_paramsadd_back(&var_to_fill->head_params, new_node);
		temp = temp->next;
	}
}

t_env_vars	*copy_env(t_env_vars *env)
{
	t_env_vars	*copy_env;
	t_var		*temp;
	t_var		*new_node;

	if (!env)
		return (NULL);
	temp = env->head_var;
	copy_env = malloc_gb(sizeof(t_env_vars));
	if (!copy_env)
		return (NULL);
	copy_env->head_var = NULL;
	while (temp)
	{
		new_node = malloc_gb(sizeof(t_var));
		if (!new_node)
			return (NULL);
		new_node->head_params = NULL;
		new_node->next = NULL;
		new_node->value = ft_strdup_gb(temp->value);
		if (!new_node->value)
		{
			free_env(copy_env);
			free_env(env);
			return (NULL);
		}
		if (temp->head_params)
			copy_param(new_node, temp);
		ft_varsadd_back(&copy_env->head_var, new_node);
		temp = temp->next;
	}
	return (copy_env);
}
