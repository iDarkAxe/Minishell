/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/22 11:28:39 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
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
	char	**toks;

	(void)command;
	(void)pid;
	path = ft_strjoin("/usr/bin/", tokens[0]);
	if (path == NULL)
		ft_exit((char *[]){"1", NULL});
	add_to_garbage(path);
	if (tokens == NULL || tokens[0] == NULL)
	{
		print_fd(2, "TOKENS VIDES");
		return (1);
	}
	toks = copy_toks(command);
	if (toks == NULL)
		return (-1);
	add_to_garbage(toks);
	print_toks(toks);
	pid = fork();
	if (pid == 0)
	{
		execve(path, toks, command->envp);
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
	t_command	*current;

	if (!command || !command->tokens || !command->tokens->str)
		return (1);
	current = command;
	while (current != NULL)
	{
		print_command(current);
		if (current->file_error == 1)
			break ;
		if (ft_strncmp(current->tokens->str, "echo", 4) == 0)
			ft_echo(&tokens[1], ' ');
		else if (ft_strncmp(current->tokens->str, "exit", 4) == 0)
			ft_exit(&tokens[1]);
		else
			not_builtins(current, tokens);
		current = current->next;
	}
	return (0);
}
