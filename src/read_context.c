/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/30 11:47:19 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"
#include <unistd.h>
#include "file.h"
#include "garbage.h"
#include <stdio.h>

// FIXME les commandes du path ne fonctionnent pas

/**
 * @brief Function to read the context where this function is called
 * Verify if it's used in a tty or not
 * 
 * @param envp environment
 * @return int 0 OK, 1 otherwise
 */
int	read_context(char **envp)
{
	int	ret;

	ret = isatty(STDIN_FILENO);
	if (ret != 0)
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
void	short_minishell_no_tty(char **envp)
{
	char		*line;
	char		**tokens;
	t_command	*command;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || line[0] == '\0')
			break ;
		tokens = parse_line(line);
		free(line);
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
	ft_exit_int(0);
}
