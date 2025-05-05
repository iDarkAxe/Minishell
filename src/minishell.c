/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:54:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/30 14:48:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program of the Minishell
 ******************************************************************************
 * @date 27 avril 2025
 * @mainpage Minishell
 * @section Introduction
 *
 * Make your own shell that performs worse than bash but it's yours.
 *
 ******************************************************************************
 */

#include "env.h"
#include "file.h"
#include "garbage.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

int			search_command(t_command *command, char **tokens);
char		*read_stdin(void);
int			minishell(char **envp);

/**
 * @brief Line condition to verify the return value of readline
 *
 * @param line line of readline
 * @return int 0, nothing checked, 1 is OK line, 2 is read another line
 */
static int	line_condition(char *line)
{
	if ((line != NULL && line[0] != '\0'))
		return (1);
	if (line == NULL)
		ft_exit_int(0);
	if (line[0] == '\0')
	{
		free(line);
		rl_on_new_line();
		return (2);
	}
	return (0);
}

/**
 * @brief Prototype for reading stdin
 *
 * @return char*
 */
char	*read_stdin(void)
{
	char	*prompt;
	char	*line;
	int		ret;

	while (1)
	{
		prompt = get_prompt_message();
		line = readline(prompt);
		if (ft_strncmp(prompt, DEFAULT_PROMPT, sizeof(DEFAULT_PROMPT)) != 0)
			free_element_gb(prompt);
		ret = line_condition(line);
		if (ret == 1)
			break ;
		else if (ret == 2)
			continue ;
	}
	add_to_garbage(line);
	add_history(line);
	return (line);
}

/* TODO Ouvrir les fichiers avec les modes appropriés
(READ, Write|Truncate, Append, et heredoc)
*/

/**
 * @brief Minishell that handles all the shell functions
 *
 * @param envp environmment
 * @return int
 */
int	minishell(char **envp)
{
	t_command	*command;
	char		*line;
	char		**tokens;

	signal_init();
	set_env(envp);
	read_context(envp);
	while (1)
	{
		line = read_stdin();
		tokens = parse_line(line);
		command = tokeniser(tokens, envp);
		if (!command)
			ft_exit_int(1);
		if (files_management(command) != 0)
		{
			free_array(tokens);
			continue ;
		}
		if (search_command(command, tokens) != 0)
			ft_exit_int(1);
		free_array(tokens);
		free_command(command);
	}
}
