/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:21:07 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/17 18:03:38 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"

/**
 * @brief get_param
 * @param content content to copy inside t_param 
 * @return param found
 */
t_params	*get_param(t_garbage *garbage, char *content, size_t equal)
{
	t_params	*param;

	if (!content && equal == FALSE)
		return (NULL);
	param = malloc_gb(garbage, sizeof(t_params));
	if (!param)
		return (NULL);
	param->next = NULL;
	param->value = ft_strdup_gb(garbage, content);
	if (!param->value)
	{
		free_element_gb(garbage, param);
		return (NULL);
	}
	return (param);
}

/**
 * @brief ft_paramlast go to the end of list of params
 * @param lst_params list of params
 * @return t_params 
 */
t_params	*ft_paramlast(t_params *lst_params)
{
	while (lst_params)
	{
		if (lst_params->next == NULL)
			return (lst_params);
		lst_params = lst_params->next;
	}
	return (NULL);
}

/**
 * @brief ft_paramsadd_back add sub_params in a param at the end
 * @param lst_params list of params, new params to add
 */
void	ft_paramsadd_back(t_params **lst_params, t_params *new)
{
	t_params	*pt;

	pt = NULL;
	if (!new || !lst_params)
		return ;
	if (*lst_params == NULL)
	{
		*lst_params = new;
		new->next = NULL;
		return ;
	}
	pt = ft_paramlast(*lst_params);
	pt->next = new;
	new->next = NULL;
}
