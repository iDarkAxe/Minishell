/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:21:07 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/08 10:51:46 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"

t_params	*get_param(char *content, size_t detect_equal)
{
	t_params	*param;

	if (!content && detect_equal == 0)
		return (NULL);
	param = malloc_gb(sizeof(t_params));
	if (!param)
		return (NULL);
	param->next = NULL;
	param->value = ft_strdup_gb(content);
	if (!param->value)
	{
		free_element_gb(param);
		return (NULL);
	}
	return (param);
}

void	replace_param(t_var *var, char *new_content)
{
	char	*new_value;

	if (!var)
		return ;
	new_value = ft_strdup_gb(new_content);
	if (!new_value || new_value[0] == '\0')
		return ;
	var->head_params = get_param(new_content, 0);
	if (var->head_params != NULL)
	{
		var->head_params->next = NULL;
		free_element_gb(var->head_params->value);
		var->head_params->value = new_value;
	}
}

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
