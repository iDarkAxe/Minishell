/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_no_tty.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/03 16:20:46 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "file.h"
#include "garbage.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static char	*read_stdin_gnl(t_garbage *garbage);

/**
 * @brief Function to read the context where this function is called
 * Verify if it's used in a tty or not.
 * To know, we check if stdin or stdout are attached to files or to the terminal
 * 
 * @return int 1 is interactive, 0 is not
 */
int	is_interactive(void)
{
	if (isatty(STDIN_FILENO) != 0 && isatty(STDOUT_FILENO) != 0
		&& isatty(STDERR_FILENO) != 0)
		return (1);
	return (0);
}

/**
 * @brief Executes the shell in a restricted area where there is no prompt
 * Should work exactly as the minishell function
 *
 * @param data data structure already set
 */
int	minishell_no_tty(t_data *data)
{
	char		*line;
	char		**tokens;

	if (!data)
		return (-1);
	while (1)
	{
		line = read_stdin_gnl(&data->garbage);
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
