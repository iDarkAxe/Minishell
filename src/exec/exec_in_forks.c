/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:47:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/03 14:27:44 by ppontet          ###   ########lyon.fr   */
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
	if (ft_strncmp(command->tokens->str, "|", 2) == 0)
		return (1);
	if (command->next && command->next->tokens
		&& ft_strncmp(command->next->tokens->str, "|", 2) == 0)
		return (1);
	return (0);
}

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
		if (command->file_error != 1)
			value = search_command(command, tokens, ret);
		free_garbage();
		exit(0);
	}
	waitpid(pid, NULL, 0);
	if (value != 0)
		command->return_value = not_builtins(command, tokens);
	return ;
}
