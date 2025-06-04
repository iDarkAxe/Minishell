/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/04 14:04:32 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_printf.h"
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

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	data;
// 	int		ret;
//
// 	(void)argc;
// 	(void)argv;
// 	if (argc != 1)
// 	{
// 		ft_dprintf(2, "Minishell doesn't take arguments\n");
// 		return (EXIT_FAILURE);
// 	}
// 	garbage_init(&data.garbage);
// 	signal_init();
// 	set_env(&data, envp);
// 	data.ret = 0;
// 	if (is_interactive() == 1)
// 		ret = minishell(&data);
// 	else
// 	{
// 		ft_dprintf(2, "Minishell is not made to be used");
// 		ft_dprintf(2, "without stdin, stdout or stderr !\n");
// 		return (EXIT_FAILURE);
// 	}
// 	free_garbage(&data.garbage);
// 	return (ret);
// }

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		ret;

	(void)argv;
	if (argc != 1)
	{
		ft_dprintf(2, "Minishell doesn't take arguments\n");
		return (EXIT_FAILURE);
	}
	garbage_init(&data.garbage);
	signal_init();
	set_env(&data, envp);
	data.ret = 0;
	ret = minishell(&data);
	free_garbage(&data.garbage);
	return (ret);
}
