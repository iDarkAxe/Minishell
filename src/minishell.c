/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:54:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/18 15:55:06 by ppontet          ###   ########lyon.fr   */
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
#include "get_next_line.h"
#include "exec.h"
#include "minishell.h"
#include "ft_printf.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

static char		*read_stdin(t_garbage *garbage);
static char		*read_stdin_gnl(t_garbage *garbage);
static t_bool	is_only_whitespace(const char *str);

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

	if (!data)
		return (-1);
	while (1)
	{
		line = read_stdin(&data->garbage);
		tokens = parse_line(data, line);
		if (tokens == NULL)
			continue ;
		data->command = tokeniser(data, tokens);
		if (files_management(data) != 0 || is_commands_valid(data) == 0)
		{
			ft_dprintf(2, "An error occurred in parsing, input is invalid\n");
			free_commands(&data->garbage, &data->command);
			free_array(&data->garbage, tokens);
			continue ;
		}
		search_paths(data, data->command);
		if (preparation_and_exec(data) != 1)
			ft_exit_int_np(&data->garbage, 1);
		free_array(&data->garbage, tokens);
		free_commands(&data->garbage, &data->command);
	}
}

/**
 * @brief Line condition to verify the return value of readline
 *
 * @param garbage garbage structure
 * @param line line of readline
 * @return int 0, nothing checked, 1 is OK line, 2 is read another line
 */
static int	line_condition(t_garbage *garbage, char *line)
{
	if (line != NULL && line[0] != '\0' && is_only_whitespace(line) == TRUE)
	{
		free(line);
		rl_on_new_line();
		return (2);
	}
	if (line != NULL && line[0] != '\0')
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
 * @brief Function to read stdin
 *
 * @param garbage structure
 * @return char* line rode
 */
static char	*read_stdin(t_garbage *garbage)
{
	char	*prompt;
	char	*line;
	int		ret;

	if (isatty(STDIN_FILENO) == 0)
		return (read_stdin_gnl(garbage));
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

/**
 * @brief Special read_stin using gnl
 *
 * @return char* line rode
 */
static char	*read_stdin_gnl(t_garbage *garbage)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			ft_exit_int_np(garbage, EXIT_SUCCESS);
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_to_garbage(garbage, line);
		return (line);
	}
}

/**
 * @brief Check if the string contains only whitespace characters
 * 
 * @param str string to check
 * @return t_bool 1 all whitespace, 0 otherwise
 */
t_bool	is_only_whitespace(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (FALSE);
	while (str[i])
	{
		if (!isspace((unsigned char)str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
