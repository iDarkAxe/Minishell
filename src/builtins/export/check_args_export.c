/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:41:32 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/07 14:35:47 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ft_printf.h"

#include <stdio.h>

int	check_args_export(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-')
	{
		ft_printf("bash: export: %s: invalid option\n", str);
		ft_printf("export: usage: export [-fn] [name[=value] ...] or export -p\n");
		return (2);
	}
	if (ft_isdigit(str[0]) == 1)
	{
		ft_printf("bash: export: %s: not a valid identifier\n", str);
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '@' || str[i] == ' ' || str[i] == '-')
		{
			ft_printf("bash: export: %s: not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}
