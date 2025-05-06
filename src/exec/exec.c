/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/06 11:08:57 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "garbage.h"
#include "builtins.h"

#include <stdio.h>
#include <sys/wait.h>

static int	search_command_exit(t_command *command, char **tokens, int ret);

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

	if (!command)
		return (1);
	current = command;
	while (current != NULL)
	{
		toks = copy_toks(current);
		if (toks == NULL)
			ft_exit_int(1);
		handle_redirections(current);
		if (needs_to_be_forked(current) != 0)
			executes_in_forks(current, toks, ret);
		else if (current->file_error != 1 && search_command(current, toks,
				ret) != 0)
			current->return_value = not_builtins(current, toks);
		ret = current->return_value;
		free_array(toks);
		reset_redirection(current, 0);
		current = current->next;
	}
	reset_redirection(current, 0);
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
	static char	*command_name[] = {"echo", "env", "which", "export", "unset",
		"cd", "pwd"};
	static int	(*cmd[])(char **) = {ft_echo, ft_env, ft_which, ft_export,
		ft_unset, ft_cd, ft_pwd};
	size_t		i;

	if (!command || !tokens || !tokens[0])
		return (1);
	i = 0;
	while (command_name[i])
	{
		if (ft_strncmp(tokens[0], command_name[i],
				ft_strlen(command_name[i])) == 0)
		{
			command->return_value = cmd[i](&tokens[1]);
			return (0);
		}
		i++;
	}
	if (command_name[i] == NULL)
		return (search_command_exit(command, tokens, ret));
	return (0);
}

static int	search_command_exit(t_command *command, char **tokens, int ret)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (1);
	if (ft_strncmp(tokens[0], "exit", 5) != 0)
		return (2);
	if (tokens && tokens[0] && tokens[1] == NULL)
		ft_exit_int(ret);
	else
		command->return_value = ft_exit(&tokens[1]);
	return (0);
}
