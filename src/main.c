/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/08 14:32:09 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "garbage.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	(void)argc;
	(void)argv;
	set_env(envp);
	if (minishell(envp) != 0)
		ft_exit_int(1);
	free_garbage();
	return (0);
}
