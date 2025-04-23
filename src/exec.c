/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/23 15:07:49 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>

int			search_command(t_command *command, char **tokens);
int			not_builtins(t_command *command, char **tokens);
static int	search_command_2(t_command *command, char **tokens);

// TODO VERIFIER not_builtins, wait() sans verification
// TODO Ajouter la recherche de la commande dans le PATH

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

	if (tokens == NULL || tokens[0] == NULL)
		return (1);
	path = ft_strjoin("/usr/bin/", tokens[0]);
	if (path == NULL)
		ft_exit((char *[]){"1", NULL});
	add_to_garbage(path);
	toks = copy_toks(command);
	if (toks == NULL)
		return (-1);
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

// TODO chaque commande renvoie un code d'erreur à attraper
// TODO verifier si on doit executer la commande dans un fork ou pas

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
		else if (ft_strncmp(command->tokens->str, "which", 5) == 0)
			ft_which(&tokens[0]);
		else if (search_command_2(current, tokens) != 0)
			not_builtins(current, tokens);
		current = current->next;
	}
	return (0);
}

static int	search_command_2(t_command *command, char **tokens)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (1);
	if (ft_strncmp(command->tokens->str, "env", 3) == 0)
		ft_env(command->envp);
	else if (ft_strncmp(command->tokens->str, "export", 6) == 0)
		ft_export(&tokens[1], command->envp);
	else if (ft_strncmp(command->tokens->str, "unset", 5) == 0)
		ft_unset(&tokens[1], command->envp);
	else if (ft_strncmp(command->tokens->str, "cd", 2) == 0)
		ft_cd(tokens);
	else if (ft_strncmp(command->tokens->str, "pwd", 3) == 0)
		ft_pwd(tokens);
	else
		return (1);
	return (0);
}
