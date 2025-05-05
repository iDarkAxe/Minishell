/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/02 11:37:36 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>

int			search_command(t_command *command, char **tokens);
static int	search_command_2(t_command *command, char **tokens, int ret);

// TODO verifier si on doit executer la commande dans un fork ou pas
// TODO les commandes doivent recevoir des char**, de t_command via t_tokens

/**
 * @brief Search if command is a builtin or not
 *
 * @param command command structure
 * @param tokens array of strings
 * @return int
 */
int	search_command(t_command *command, char **tokens)
{
	static int	previous_ret = 0;
	t_command	*current;

	if (!command || !command->tokens || !command->tokens->str)
		return (1);
	current = command;
	while (current != NULL)
	{
		print_command(current);
		printf("return (value is %d\n", previous_ret));
		if (current->file_error == 1)
			break ;
		if (ft_strncmp(current->tokens->str, "echo", 5) == 0)
			current->return_value = ft_echo(&tokens[1], ' ');
		else if (ft_strncmp(command->tokens->str, "which", 6) == 0)
			current->return_value = ft_which(&tokens[0]);
		else if (search_command_2(current, tokens, previous_ret) != 0)
			current->return_value = not_builtins(current, tokens);
		previous_ret = current->return_value;
		current = current->next;
	}
	return (0);
}

static int	search_command_2(t_command *command, char **tokens, int ret)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (1);
	if (ft_strncmp(command->tokens->str, "env", 4) == 0)
		command->return_value = ft_env(&tokens[1]);
	else if (ft_strncmp(command->tokens->str, "export", 7) == 0)
		command->return_value = ft_export(&tokens[1]);
	else if (ft_strncmp(command->tokens->str, "unset", 6) == 0)
		command->return_value = ft_unset(&tokens[1]);
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
