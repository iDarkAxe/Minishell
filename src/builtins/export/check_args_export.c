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

int	check_args_export(const char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-')
	{
		ft_dprintf(2, "minishell: export: %s: invalid option\n", str);
		ft_dprintf(2, "export: usage: export [-fn] [name[=value] ...] or export\
			-p\n");
		return (2);
	}
	else if (str[0] == '=' || ft_isdigit(*str) == 1 || str[0] == '?')
	{
		ft_dprintf(2, "minishell: export: %s: not a valid identifier\n", str);
		return (1);

	}
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '@' || str[i] == ' ' || str[i] == '-') 
		{
				ft_dprintf(2, "minishell: export: %s: not a valid identifier\n",
					str);
				return (1);
		}
		i++;
	}
	// while (str[i] && str[i] == '=')
	// {
	// 	if (ft_isdigit(str[i]) == 1)
	// 	{
	// 		ft_dprintf(2, "minishell: export: %s: not a valid identifier\n",
	// 			str);
	// 		return (1);
	// 	}
	// 	i++;
	// }
	return (0);
}
