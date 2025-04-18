/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/18 14:51:43 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>

int	search_command(t_command *command, char **tokens);
int	not_builtins(t_command *command, char **tokens);

// TODO VERIFIER not_builtins, wait() sans verification

/**
 * @brief Executes commands that are not builtins
 *
 * @param command command structure
 * @param tokens array of strings
 * @return int
 */
int	not_builtins(t_command *command, char **tokens)
{
	int		pid;
	char	*path;

	path = ft_strjoin("/usr/bin/", tokens[0]);
	if (path == NULL)
		ft_exit((char *[]){"1", NULL});
	add_to_garbage(path);
	pid = fork();
	if (pid == 0)
	{
		execve(path, tokens, command->envp);
		perror("execve");
		ft_exit((char *[]){"1", NULL});
	}
	free_element_gb(path);
	wait(NULL);
	return (0);
}

/**
 * @brief Search if command is a builtin or not
 *
 * @param command command structure
 * @param tokens array of strings
 * @return int
 */
int	search_command(t_command *command, char **tokens)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (1);
	if (ft_strncmp(command->tokens->str, "echo", 4) == 0)
		ft_echo(&tokens[1], ' ');
	else if (ft_strncmp(command->tokens->str, "exit", 4) == 0)
		ft_exit(&tokens[1]);
	else
		not_builtins(command, tokens);
	return (0);
}
