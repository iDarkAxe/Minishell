/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/03 17:16:15 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// READLINE
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
// OTHER
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	*prompt;

	(void)argc;
	(void)argv;
	(void)envp;
	signal_init();
	prompt = get_prompt_message();
	if (prompt == NULL)
	{
		free_garbage();
		write(2, "Error creating prompt\n", 22);
		exit(1);
	}
	str = readline(prompt);
	if (str == NULL)
		return (-1);
	add_history(str);
	add_to_garbage(str);
	free_garbage();
}
