/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/28 14:44:30 by ppontet          ###   ########lyon.fr   */
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
	int		ret;

	(void)argc;
	(void)argv;
	garbage_init(&data.garbage);
	signal_init();
	set_env(&data, envp);
	data.ret = 0;
	if (is_interactive() == 1)
		ret = minishell(&data);
	else
		ret = short_minishell_no_tty(&data);
	free_garbage(&data.garbage);
	return (0);
}
