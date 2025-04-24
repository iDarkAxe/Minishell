/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:01:37 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/23 14:54:50 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
	if (*var == NULL)
	{
		*var = new;
		return ;
	}
	pt = ft_varlast(*var);
	pt->next = new;
}

t_params	*ft_paramlast(t_params *params)
{
	while (params)
	{
		if (params->next == NULL)
			return (params);
		params = params->next;
	}
	return (NULL);
}

void	ft_paramsadd_back(t_params **params, t_params *new)
{
	t_params	*pt;

	pt = NULL;
	if (*params == NULL)
	{
		*params = new;
		new->next = NULL;
		return ;
	}
	pt = ft_paramlast(*params);
	pt->next = new;
	new->next = NULL;
}

int	count_env(t_env_vars env)
{
	int	count;

	count = 0;
	if (!env.head_var)
		return (0);
	while (env.head_var)
	{
		count++;
		env.head_var = env.head_var->next;
	}
	return (count);
}
