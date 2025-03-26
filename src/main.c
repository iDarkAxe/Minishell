/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/26 14:47:04 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// READLINE
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
// OTHER
#include "minishell.h"
#include "garbage.h"
#include <stdlib.h>
#include <unistd.h>

#include "pipex.h"

int	main(void)
{
	char	*str;
	char	*prompt;

	signal_init();
	prompt = get_prompt_message();
	if (prompt == NULL)
	{
		free_garbage();
		write(2, "Error creating prompt\n", 22);
		exit(1);
	}
	str = readline(prompt);
	while (1)
	{
		if (str)
			printf("%s\n", str);
		else
			break ;
		printf("\n");
		usleep(500000);
	}
	free_garbage();
	exec(4, (char *[]){"test", "bonjour"}, (char *[]){"test", "bonjour"});
}
