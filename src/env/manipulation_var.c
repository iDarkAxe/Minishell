/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>        +  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:01:37 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/23 12:07:52 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "garbage.h"

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

void	ft_varsadd_front(t_var **var, t_var *new)
{
	if (!new)
		return ;
	new->next = *var;
	*var = new;
}

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
