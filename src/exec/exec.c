/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/09 16:34:34 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"

#include <unistd.h>
#include <wait.h>

/**
 * @brief Prepare the command for search_command()
 *
 * @param command command structure
 * @return int
 */
int	prepare_command(t_command *command, int ret)
{
	char	**toks;

	if (!command)
		ft_exit_int_np(1);
	toks = copy_toks(command);
	if (toks == NULL)
		ft_exit_int_np(1);
	handle_redirections(command);
	if (command->file_error != 1 && search_command(command, toks, ret) != 0)
		command->return_value = not_builtins(command, toks);
	free_array(toks);
	reset_redirection(command, 0);
	return (command->return_value);
}

void	fill_toks_into_commands(t_command *command)
{
	t_command	*current;
	char		**toks;

	current = command;
	while (current)
	{
		toks = copy_toks(current);
		if (toks == NULL)
		{
			free_garbage();
			exit(EXIT_FAILURE);
		}
		current->toks = toks;
		current = current->next;
	}
}

// FIXME IT"S ONLY A PLACEHOLDER DON'T BE CONFUSED
void	search_paths(t_command *command)
{
	t_command	*current;

	current = command;
	while (current)
	{
		if (!current->toks || !current->toks[0])
			current->path = "NULL";
		else
			current->path = ft_strjoin("/usr/bin/", current->toks[0]);
		if (current->path == NULL)
		{
			free_garbage();
			exit(EXIT_FAILURE);
		}
		add_to_garbage(current->path);
		current = current->next;
	}
}

int	prepare_command_forks(t_command *command, int ret)
{
	pid_t		*pids;
	size_t		cmd_count;
	t_command	*current;

	if (!command)
		ft_exit_int_np(1);
	cmd_count = count_commands(command);
	fill_toks_into_commands(command);
	search_paths(command);
	pids = malloc_gb(sizeof(pid_t) * cmd_count);
	if (!pids)
	{
		free_garbage();
		exit(EXIT_FAILURE);
	}
	execute_pipeline(command, pids, ret);
	ignore_signal();
	wait_all_childs(command, pids);
	free_element_gb(pids);
	signal_init();
	current = command;
	while (current && current->next)
		current = current->next;
	return (current->return_value);
}
