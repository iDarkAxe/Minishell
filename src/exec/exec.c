/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/03 14:27:42 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "garbage.h"
#include "libft.h"
#include "builtins.h"

#include <stdio.h>
#include <sys/wait.h>

// TODO verifier si on doit executer la commande dans un fork ou pas
// TODO add free pipes in case of forks

/**
 * @brief Prepare the command for search_command()
 *
 * @param command command structure
 * @return int
 */
int	prepare_command(t_command *command)
{
	static int	ret = 0;
	t_command	*current;
	char		**toks;

	if (!command || !command->tokens || !command->tokens->str)
		return (1);
	current = command;
	while (current != NULL)
	{
		print_command(current);
		toks = copy_toks(current);
		if (toks == NULL)
			ft_exit_int(1);
		handle_redirections(current);
		if (needs_to_be_forked(command) != 0)
			executes_in_forks(current, toks, ret);
		else if (current->file_error != 1 && search_command(current, toks,
				ret) != 0)
			current->return_value = not_builtins(current, toks);
		ret = current->return_value;
		free_array(toks);
		reset_redirection(current, 0);
		current = current->next;
	}
	return (0);
}

/**
 * @brief  Search if command is a builtin or not
 *
 * @param command command structure
 * @param tokens array of strings
 * @param ret return value of previous command
 * @return int 0 if command found, 1 otherwise
 */
int	search_command(t_command *command, char **tokens, int ret)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (1);
	if (ft_strncmp(command->tokens->str, "echo", 5) == 0)
		command->return_value = ft_echo(&tokens[1], ' ');
	else if (ft_strncmp(command->tokens->str, "env", 4) == 0)
		command->return_value = ft_env(command->envp);
	else if (ft_strncmp(command->tokens->str, "which", 6) == 0)
		command->return_value = ft_which(&tokens[0]);
	else if (ft_strncmp(command->tokens->str, "export", 7) == 0)
		command->return_value = ft_export(&tokens[1], command->envp);
	else if (ft_strncmp(command->tokens->str, "unset", 6) == 0)
		command->return_value = ft_unset(&tokens[1], command->envp);
	else if (ft_strncmp(command->tokens->str, "cd", 3) == 0)
		command->return_value = ft_cd(tokens);
	else if (ft_strncmp(command->tokens->str, "pwd", 4) == 0)
		command->return_value = ft_pwd(tokens);
	else if (ft_strncmp(command->tokens->str, "exit", 5) == 0
		&& command->tokens->next == NULL)
		ft_exit_int(ret);
	else if (ft_strncmp(command->tokens->str, "exit", 5) == 0)
		command->return_value = ft_exit(&tokens[1]);
	else
		return (1);
	return (0);
}
