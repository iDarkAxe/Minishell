/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:41:32 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/11 13:48:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int	check_args_export(char *str, size_t size)
{
	size_t	i;
	char	var[size];

	i = 0;
	ft_memcpy(var, str, size);
	var[size] = '\0';
	printf("Inside check args : %s\n", var);
	if (var[0] == '-')
	{
		ft_dprintf(2, "minishell: export: %s: invalid option\n", var);
		ft_dprintf(2, "export: usage: export [-fn] [name[=value] ...] or export\
			-p\n");
		return (2);
	}
	if (ft_isdigit(var[0]) == 1)
	{
		ft_dprintf(2, "minishell: export: %s: not a valid identifier\n", var);
		return (1);
	}
	while (var[i])
	{
		if (var[i] == '@' || var[i] == ' ' || var[i] == '-')
		{
			ft_dprintf(2, "minishell: export: %s: not a valid identifier\n",
				var);
			return (1);
		}
		i++;
	}
	return (0);
}
