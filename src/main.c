/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/17 16:35:49 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// READLINE
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
// OTHER
#include "file.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

int		minishell(int argc, char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**tokens;
	t_command	*command;

	(void)argc;
	(void)argv;
	(void)envp;
	line = "cat \"'my file.txt'\" < infile >> outfile | gr\"ep\" hello \
	>> 		out.txt |grep \"test\" > file";
	tokens = lexer(line);
	if (tokens == NULL)
		ft_exit((char *[]){"1", NULL});
	command = tokeniser(tokens);
	if (!command)
		ft_exit((char *[]){"1", NULL});
	print_command(command);
	files_management(command);
	print_command(command);
	free_char_tokens(tokens);
	free_command(command);
	free_garbage();
	return (0);
}

/**
 * @brief Minishell prototype
 *
 * @param argc number of arguments
 * @param argv array of string
 * @param envp environmment
 * @return int
 */
int	minishell(int argc, char **argv, char **envp)
{
	t_command	*command;
	char		*prompt;
	char		*line;
	char		**tokens;
	int			pid;

	(void)argc;
	(void)argv;
	signal_init();
	while (1)
	{
		prompt = get_prompt_message();
		if (prompt == NULL)
		{
			free_garbage();
			ft_exit((char *[]){"1", NULL});
		}
		line = readline(prompt);
		free_element_gb(prompt);
		if (line == NULL)
			break ;
		add_history(line);
		tokens = lexer(line);
		if (tokens == NULL)
			ft_exit((char *[]){"1", NULL});
		command = tokeniser(tokens);
		if (!command)
			ft_exit((char *[]){"1", NULL});
		print_command(command);
		files_management(command);
		print_list_files(command);
		if (ft_strncmp(line, "exit", 4) == 0)
			ft_exit(&tokens[1]);
		if (ft_strncmp(line, "clear", 4) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve("/usr/bin/clear", (char *[]){"clear", NULL}, envp);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			write(1, "ici\n", 4);
		}
	}
	free_garbage();
	return (0);
}
