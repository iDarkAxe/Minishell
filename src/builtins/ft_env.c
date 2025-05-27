/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:44:08 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/22 15:19:37 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

int		ft_env(t_data *data, char **array);
void	print_env(t_env_vars *env);

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
		if (param)
		{
			printf("%s=", var->value);
			while (param)
			{
				printf("%s", param->value);
				if (param->next)
					printf(":");
				param = param->next;
			}
			printf("\n");
		}
		var = var->next;
	}
}

int	ft_env(t_data *data, char **array)
{
	t_env_vars	*env;

	env = &data->env;
	(void)array;
	if (array[0] != NULL)
	{
		printf("env: '%s': No such file or directory\n", array[0]);
		return (-1);
	}
	print_env(env);
	return (0);
}
