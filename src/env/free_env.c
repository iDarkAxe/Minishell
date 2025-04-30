/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:39:36 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/29 16:50:04 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

void	free_params(t_params *params)
{
	t_params	*temp;

	temp = params;
	if (!params)
		return ;
	while (temp != NULL)
	{
		temp = params->next;
		free(params->value);
		free(params);
	}
	return ;
}

void	free_vars(t_env_vars *env)
{
	t_var	*temp;

	if (!env)
		return ;
	temp = env->head_var;
	while (temp != NULL)
	{
		temp = temp->next;
	}
	return ;
}
