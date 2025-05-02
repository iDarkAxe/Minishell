/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:21:06 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/02 17:38:25 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	print_env_vars(t_env_vars *env)
{
	t_var		*var;
	t_params	*param;

	if (!env)
		return ;
	var = env->head_var;
	while (var)
	{
		param = var->head_params;
		if (param != NULL)
			printf("%s=", var->value);
		while (param)
		{
			printf("%s", param->value);
			if (param->next)
				printf(":");
			param = param->next;
		}
		printf("\n");
		var = var->next;
	}
}
