/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/01 16:45:25 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>

static int	search_command_2(t_command *command, char **tokens, int ret);

// TODO verifier si on doit executer la commande dans un fork ou pas

/**
 * @brief Search if command is a builtin or not
 *
 * @param command command structure
 * @return int
 */
int	search_command(t_command *command)
{
	static int	previous_ret = 0;
	t_command	*current;
	char		**toks;

	if (!command || !command->tokens || !command->tokens->str)
		return (1);
	current = command;
	while (current != NULL)
	{
		print_command(current);
		if (current->file_error == 1)
			break ;
		toks = copy_toks(current);
		if (toks == NULL)
			ft_exit_int(1);
		handle_redirections(current);
		if (search_command_2(current, toks, previous_ret) != 0)
			current->return_value = not_builtins(current, toks);
		previous_ret = current->return_value;
		free_array(toks);
		free_pipes(current);
		current = current->next;
	}
	return (0);
}

static int	search_command_2(t_command *command, char **tokens, int ret)
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
