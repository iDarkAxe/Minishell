/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_alt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:58:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/04 12:38:46 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

void		ft_exit_int(t_garbage *garbage,
				int value) __attribute__((noreturn));
void		ft_exit_int_np(t_garbage *garbage,
				int value) __attribute__((noreturn));

/**
 * @brief Short ft_exit that uses only int
 * noreturn attribute is to prevent -Wmissing-noreturn flag
 * from flag -Weverything of debug-cc
 *
 * @param garbage garbage structure
 * @param value value
 */

void	ft_exit_int(t_garbage *garbage, int value)
{
	free_garbage(garbage);
	if (is_interactive() == 1)
		ft_dprintf(2, "exit\n");
	exit((unsigned char)value);
}

/**
 * @brief Short ft_exit that uses only int but don't say it's name
 *
 * @param garbage garbage structure
 * @param value value
 */
void	ft_exit_int_np(t_garbage *garbage, int value)
{
	free_garbage(garbage);
	exit((unsigned char)value);
}
