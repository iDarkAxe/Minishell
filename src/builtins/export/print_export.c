/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:19:35 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/02 16:33:16 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	print_var(t_var **var, t_params **param)
{
	if (ft_isalpha((*var)->value[0]) == 1)
	{
		if (FOLLOW_ZSH == 0)
			ft_putstr_fd("declare -x ", 1);
		printf("%s=", (*var)->value);
	}
	*param = (*var)->head_params;
}

void	print_export(t_env_vars *env)
{
	t_var		*var;
	t_params	*param;

	if (!env)
		return ;
	var = env->head_var;
	while (var)
	{
		print_var(&var, &param);
		while (param)
		{
			if (ft_isalpha(var->value[0]) == 1)
			{
				printf("%s", param->value);
				if (param->next)
					printf(":");
				param = param->next;
			}
			else
				break ;
		}
		printf("\n");
		var = var->next;
	}
}
