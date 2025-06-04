/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:58:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/04 19:36:16 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "builtins.h"
#include "minishell.h"

void	check_args_exit(t_data *data, char **array);

void	check_args_exit(t_data *data, char **array)
{
	int	value;

	if (array == NULL || array[0] == NULL)
	{
		value = data->ret;
		free_garbage(&data->garbage);
		print_exit(value);
		exit(value);
	}
	if (array && array[0] && array[0][0] == '\0')
	{
		value = data->ret;
		ft_dprintf(2, "minishell: exit: : numeric argument required\n");
		free_garbage(&data->garbage);
		print_exit(value);
		exit(value);
	}
}
