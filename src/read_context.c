/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/09 16:28:55 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "file.h"
#include "garbage.h"
#include "get_next_line.h"
#include "builtins.h"

#include <stdio.h>
#include <unistd.h>

// FIXME les commandes du path ne fonctionnent pas

static char	*read_stdin_gnl(void);

/**
 * @brief Function to read the context where this function is called
 * Verify if it's used in a tty or not
 *
 * @param envp environment
 * @return int 0 OK, 1 otherwise
 */
int	read_context(char **envp)
{
	if (isatty(STDIN_FILENO) != 0 && isatty(STDOUT_FILENO) != 0)
		return (0);
	short_minishell_no_tty(envp);
	return (0);
}

/**
 * @brief Executes the shell in a restricted area where there is no prompt
 * Should work exactly as the minishell function
 *
 * @param envp environment
 */
__attribute__ ((noreturn))
void	short_minishell_no_tty(char **envp)
{
	static int	ret = 0;
	char		*line;
	char		**tokens;
	t_command	*command;

	while (1)
	{
		line = read_stdin_gnl();
		tokens = parse_line(line);
		free(line);
		command = tokeniser(tokens, envp);
		if (command->tokens->str == NULL || files_management(command) != 0)
		{
			free_command(command);
			free_array(tokens);
			continue ;
		}
		if (needs_to_be_forked(command) != 0)
			ret = prepare_command_forks(command, ret);
		else
			ret = prepare_command(command, ret);
		free_array(tokens);
		free_command(command);
	}
}

/**
 * @brief Special read_stin using gnl
 * 
 * @return char* line rode
 */
static char	*read_stdin_gnl(void)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			ft_exit_int_np(0);
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		return (line);
	}
}
