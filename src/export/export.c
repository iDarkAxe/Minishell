/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:35 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/28 17:25:13 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"

static t_var *get_var(const char *var)
{
	t_var	*new;

	new = malloc_gb(sizeof(t_var));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->value = ft_strdup_gb(var);
	if (!new->value)
		return (NULL);
	return (new);
}

static t_params	*get_param(char *content)
{
	t_params	*param;

	param = malloc_gb(sizeof(t_params));
	if (!param)
		return (NULL);
	param->value = ft_strdup_gb(content);
	if (!param->value)
		return (NULL);
	return (param);
}

// static	void	fill_new_var(t_var **new, char *var, char *content)
// {
// 	*new = get_var(var);
// 	if (!new)
// 		return ;
// 	(*new)->head_params = get_param(content);
// 	if (!(*new)->head_params)
// 		return ;
// }

void	add_var_and_param(t_env_vars *env, char *var, char *content)
{
	t_var	*new;

	new = get_var(var); 
	if (!new)
		return ;
	new->head_params = get_param(content);
	if (!new->head_params)
		return ;
	return ;
}
