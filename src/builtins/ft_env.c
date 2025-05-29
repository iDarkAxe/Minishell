/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:44:08 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/29 12:54:02 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "ft_printf.h"

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
			ft_printf("%s=", var->value);
			while (param)
			{
				ft_printf("%s", param->value);
				if (param->next)
					ft_printf(":");
				param = param->next;
			}
			ft_printf("\n");
		}
		var = var->next;
	}
}

int	ft_env(t_data *data, char **array)
{
	t_env_vars	*env;

	env = &data->env;
	if (array[0] != NULL)
	{
		ft_dprintf(2, "minishell: env: '%s': No such file or directory\n",
			array[0]);
		return (-1);
	}
	print_env(env);
	return (0);
}
