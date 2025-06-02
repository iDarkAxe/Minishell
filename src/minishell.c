/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:54:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/02 10:42:50 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/**
 ******************************************************************************
 * @file           : minishell.c
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
#include "builtins.h"
#include "env.h"
#include "file.h"
#include "garbage.h"
#include "exec.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

static char	*read_stdin(t_garbage *garbage);

/**
 * @brief Minishell that handles all the shell functions
 *
 * @param data data structure already set
 * @return int
 */
int	minishell(t_data *data)
{
	char	*line;
	char	**tokens;
	char	**envp;

	if (!data)
		return (-1);
	envp = NULL;
	while (1)
	{
		line = read_stdin(&data->garbage);
		tokens = parse_line(data, line);
		data->command = tokeniser(data, tokens);
		if (data->command->tokens->str == NULL || files_management(data) != 0)
		{
			free_commands(&data->garbage, &data->command);
			free_array(&data->garbage, tokens);
			continue ;
		}
		if (needs_to_be_forked(data->command) != 0)
			data->ret = prepare_command_forks(data);
		else
			data->ret = prepare_command(data);
		free_array(&data->garbage, tokens);
		free_commands(&data->garbage, &data->command);
	}
}

/**
 * @brief Line condition to verify the return value of readline
 *
 * @param line line of readline
 * @return int 0, nothing checked, 1 is OK line, 2 is read another line
 */
static int	line_condition(t_garbage *garbage, char *line)
{
	if ((line != NULL && line[0] != '\0'))
		return (1);
	if (line == NULL)
		ft_exit_int(garbage, 1);
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
static char	*read_stdin(t_garbage *garbage)
{
	char	*prompt;
	char	*line;
	int		ret;

	while (1)
	{
		prompt = get_prompt_message(garbage);
		line = readline(prompt);
		if (ft_strncmp(prompt, DEFAULT_PROMPT, sizeof(DEFAULT_PROMPT)) != 0)
			free_element_gb(garbage, prompt);
		ret = line_condition(garbage, line);
		if (ret == 1)
			break ;
		else if (ret == 2)
			continue ;
	}
	add_to_garbage(garbage, line);
	add_history(line);
	return (line);
}
