/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:01:37 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 14:44:04 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "garbage.h"

/**
 * @brief ft_varlast go to the end of list of t_var
 * @param var list of t_var
 * @return t_var or NULL if no t_var inside the list
 */
t_var	*ft_varlast(t_var *var)
{
	while (var)
	{
		if (var->next == NULL)
			return (var);
		var = var->next;
	}
	return (NULL);
}

/**
 * @brief ft_varsadd_back add a t_var inside a list of t_var at the end
 * @param var reference of t_var
 * @param new t_var have to add in a list of t_var
 */
void	ft_varsadd_back(t_var **var, t_var *new)
{
	t_var	*pt;

	pt = NULL;
	if (new == NULL)
		return ;
	if (*var == NULL)
	{
		*var = new;
		return ;
	}
	pt = ft_varlast(*var);
	pt->next = new;
}

/**
 * @brief ft_varsadd_front add a t_var inside a list of t_var at the beginning
 * @param var reference of t_var
 * @param new t_var have to add in a list of t_var
 */
void	ft_varsadd_front(t_var **var, t_var *new)
{
	if (!new)
		return ;
	new->next = *var;
	*var = new;
}

/**
 * @brief get_var allow to create a t_var
 * @param var string allow to create t_var
 * @return t_var
 */
t_var	*get_var(t_garbage *garbage, const char *var)
{
	t_var	*new;

	new = malloc_gb(garbage, sizeof(t_var));
	if (!new)
		ft_exit_int(garbage, -1);
	new->head_params = NULL;
	new->next = NULL;
	new->value = ft_strdup_gb(garbage, var);
	if (!new->value)
	{
		free_element_gb(garbage, new);
		return (NULL);
	}
	return (new);
}
