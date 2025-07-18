/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:19:35 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/17 11:43:54 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_printf.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"

static void	print_var(t_var *var)
{
	if (ft_isalpha(var->value[0]) == 1 || !(var->value[0] == '_'
			&& var->value[1] == '\0'))
	{
		if (FOLLOW_ZSH == 0)
			ft_putstr_fd("declare -x ", 1);
		if (var->head_params && var->head_params->value != NULL)
			ft_printf("%s=", var->value);
		else
			ft_printf("%s", var->value);
	}
}

static void	print_params(t_var *var)
{
	t_params	*param;

	param = var->head_params;
	ft_printf("\"");
	while (param && param->value != NULL)
	{
		ft_printf("%s", param->value);
		if (param->next)
			ft_printf(":");
		param = param->next;
	}
	ft_printf("\"\n");
}

void	print_export(t_env_vars *env)
{
	t_var		*var;
	t_params	*param;

	if (!env)
		return ;
	var = env->head_var;
	param = NULL;
	while (var)
	{
		print_var(var);
		param = var->head_params;
		if ((param && param->value) && (ft_isalpha(var->value[0]) == 1
				|| !(var->value[0] == '_' && var->value[1] == '\0')))
			print_params(var);
		if (!param)
			ft_printf("\n");
		var = var->next;
	}
}
