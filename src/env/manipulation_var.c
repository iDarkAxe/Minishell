/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:01:37 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/08 14:20:39 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "builtins.h"

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

t_var	*get_var(const char *var)
{
	t_var	*new;

	new = malloc_gb(sizeof(t_var));
	if (!new)
		ft_exit_int(-1);
	ft_bzero(new, sizeof(t_var));
	new->next = NULL;
	new->value = ft_strdup_gb(var);
	if (!new->value)
	{
		free_element_gb(new);
		ft_exit_int(-1);
	}
	return (new);
}
