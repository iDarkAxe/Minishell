/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/15 10:50:49 by ppontet          ###   ########lyon.fr   */
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

t_command	*tokeniser(char **tokens);

int	main(void)
{
	t_command	*command;
	char		*line;
	char		**tokens;

	line = "cat \"'my file.txt'\" < infile << eof >> outfile | gr\"ep\" hello \
	>> 	 out.txt |grep \"test\" > file";
	tokens = lexer(line);
	if (tokens == NULL)
	{
		free_garbage();
		write(2, "Error creating tokens\n", 22);
		exit(1);
	}
	command = tokeniser(tokens);
	if (!command)
	{
		free_garbage();
		write(2, "Error creating command structure\n", 33);
		exit(1);
	}
	print_command(command);
	free_garbage();
	return (0);
}
