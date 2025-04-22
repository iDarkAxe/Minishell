/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/22 17:14:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "garbage.h"
#include "minishell.h"
#include "garbage.h"
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (minishell(envp) != 0)
		ft_exit((char *[]){"1", NULL});
	if (minishell(envp) != 0)
		ft_exit((char *[]){"1", NULL});
	free_garbage();
	return (0);
}
