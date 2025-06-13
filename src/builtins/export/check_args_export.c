/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:41:32 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 11:53:24 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include "parsing.h"

static int	check_args_export_to_end(const char *str, size_t i);

/**
 * @brief check_args_export check if the argument of eport is correct 
 * @param str string to check 
 * @return 0 if is ok, superior to 1 isn't ok 
 */
int	check_args_export(const char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-')
	{
		ft_dprintf(2, "minishell: export: %s: invalid option\n", str);
		ft_dprintf(2, "export: usage: export [-fn] [name[=value] ...]");
		ft_dprintf(2, " or export -p\n ");
			return (2);
	}
	else if (str[0] == '=' || ft_isdigit(*str) == 1 || str[0] == '?')
	{
		ft_dprintf(2, "minishell: export: %s: not a valid identifier\n", str);
		return (1);
	}
	if (check_args_export_to_end(str, i) == 1)
		return (1);
	return (0);
}

/**
 * @brief check_args_export_to_end check if the argument of export
 * @param str string to check i position inside the string 
 * @return 0 if is ok, superior to 1 isn't ok 
 */
static int	check_args_export_to_end(const char *str, size_t i)
{
	if (!str)
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && ft_is_special_character(str[i]))
		{
			ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n",
				str);
			return (1);
		}
		i++;
	}
	return (0);
}
