/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>        +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:44:08 by lud-adam           #+#    #+#            */
/*   Updated: 2025/06/12 16:52:26 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "ft_printf.h"

int		ft_env(t_data *data, char **array);
void	print_env(t_env_vars *env);

/**
 * @brief print_env allow to display the shell environment 
 * @param env env is the shell environment
 * @return 
 */
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

/**
 * @brief ft_env allow to display the shell environment 
 * @param char **array array of string with arguments for the function
 * @return int 0 if is ok
 */
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
