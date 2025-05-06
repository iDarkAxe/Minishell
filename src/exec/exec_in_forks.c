/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:47:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/06 16:33:30 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "garbage.h"

#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief Check if it needs to be forked
 *
 * @param command command structure
 * @return int 0 NO, 1 YES
 */
int	needs_to_be_forked(t_command *command)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (0);
	if (ft_strncmp(command->tokens->str, "|", 2) == 0)
	{
		dprintf(2, "here fork %s\n", command->tokens->str);
		return (1);
	}
	if (command->next && command->next->tokens
		&& ft_strncmp(command->next->tokens->str, "|", 2) == 0)
	{
		dprintf(2, "preced fork %s\n", command->next->tokens->str);
		return (1);
	}
	return (0);
}

// FIXME SIGPIPE kill the process ? so it ends instant

/**
 * @brief Executes the command in a forks
 *
 * @param command command structure
 * @param tokens array of strings
 * @param ret return value of previous command
 */
void	executes_in_forks(t_command *command, char **tokens, int ret)
{
	int	pid;
	int	value;

	if (!command || !command->tokens)
		return ;
	if (ft_strncmp(command->tokens->str, "|", 2) == 0)
		command->tokens = command->tokens->next;
	value = 0;
	pid = fork();
	if (pid == 0)
	{
		reset_signal_default();
		if (command->file_error != 1)
			value = search_command(command, tokens, ret);
		free_garbage();
		exit(0);
	}
	ignore_signal();
	waitpid(pid, NULL, 0);
	signal_init();
	if (value != 0)
		command->return_value = not_builtins(command, tokens);
	return ;
}
