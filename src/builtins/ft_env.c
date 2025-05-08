/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:44:08 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/06 11:09:04 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

void	print_env(t_env_vars *env)
{
	t_var		*var;
	t_params	*param;

	if (!env)
		return ;
	var = env->head_var;
	while (var)
	{
		param = var->head_params;
		if (param && param->value[0])
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

int	ft_env(char **array)
{
	t_env_vars	*env;

	env = get_env();
	(void)array;
	if (array[0] != NULL)
	{
		printf("env: '%s': No such file or directory\n", array[0]);
		return (-1);
	}
	print_env(env);
	return (0);
}
