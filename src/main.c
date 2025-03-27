/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/27 15:00:06 by ppontet          ###   ########lyon.fr   */
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
	int		pid;

	(void)argc;
	(void)argv;
	signal_init();
	prompt = get_prompt_message();
	if (prompt == NULL)
	{
		free_garbage();
		write(2, "Error creating prompt\n", 22);
		exit(1);
	}
	while (1)
	{
		str = readline(prompt);
		if (str == NULL)
			break ;
		if (str[0] == '\0')
			continue ;
		add_history(str);
		add_to_garbage(str);
		pid = fork();
		if (pid == 0)
			execve("/bin/bash", (char *[]){"bash", "-c", str, NULL}, envp);
		free_element_gb(str);
		// usleep(10000);
	}
	free_garbage();
}
