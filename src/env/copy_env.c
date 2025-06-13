/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:41:13 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 13:41:52 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "garbage.h"
#include <stdlib.h>

/**
 * @brief supp_var function to supp a var in env 
 *
 * @param head of t_var to search the var to supp, 
 * @param str allow to identify the var to supp
 */
void	supp_var(t_garbage *garbage, t_var **head, char *str)
{
	t_supp	*supp;

	if (!head || !str)
		return ;
	supp = malloc_gb(garbage, sizeof(t_supp));
	if (!supp)
		return ;
	supp->curr = *head;
	supp->prev_str = NULL;
	while (supp->curr != NULL)
	{
		if (ft_strcmp(supp->curr->value, str) == 0)
		{
			if (supp->prev_str)
				supp->prev_str->next = supp->curr->next;
			else
				*head = supp->curr->next;
			free_params(garbage, supp->curr->head_params);
			free_element_gb(garbage, supp->curr);
			break ;
		}
		supp->prev_str = supp->curr;
		supp->curr = supp->curr->next;
	}
}

/**
 * @brief search_env_var search an environment variable inside the environment 
 *
 * @param env environment to search,  
 * @param var variable to search inside the envrionment 
 * @return t_var or NULL if no variable find
 */
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

/**
 * @brief copy_param allow to copy the params of a t_var
 *
 * @param var_to_fill var has to fill, 
 * @param content has to copy 
 */
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

/**
 * @brief free_all_and_exit free and exit
 *
 * @param env and c_env elements to free
 */
void static	free_all_and_exit(t_garbage *garbage, t_env_vars *env,
		t_env_vars *c_env)
{
	free_env(garbage, env);
	free_env(garbage, c_env);
	ft_exit_int(garbage, -1);
}

/**
 * @brief copy_env allow to copy the env
 *
 * @param env environment to copy
 * @return t_env_vars 
 */
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
