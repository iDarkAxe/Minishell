/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/23 11:59:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "builtins.h"
#include "env.h"
#include "garbage.h"
#include "minishell.h"

/**
 * @brief Main function
 *
 * @param argc number of argument
 * @param argv array of arguments
 * @param envp environment
 * @return int 0 OK, error otherwise
 */
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.command = NULL;
	// set_env(&data, envp);
	if (minishell(envp) != 0)
		ft_exit_int_np(1);
	free_garbage(&data.garbage);
	return (0);
}
