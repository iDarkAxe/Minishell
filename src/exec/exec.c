/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/04 12:21:20 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "exec.h"
#include <unistd.h>
#include <wait.h>

/**
 * @brief Prepare the command for search_command()
 *
 * @param data data structure
 * @return int
 */
int	prepare_command(t_data *data)
{
	int		fd[2];

	if (!data || !data->command)
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	if (data->command->parse_error == 1)
		return (data->command->return_value);
	data->command->toks = copy_toks(data, data->command);
	if (data->command->toks == NULL)
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	handle_redirections(&data->garbage, data->command, fd);
	if (data->command->file_error != 1 && search_command(data, data->command,
			data->command->toks) != 0)
		data->command->return_value = not_builtins(data, data->command,
				data->command->toks);
	reset_redirection(&data->garbage, data->command, fd, 0);
	return (data->command->return_value);
}

void	fill_toks_into_commands(t_data *data, t_command *command)
{
	t_command	*current;
	char		**toks;

	current = command;
	while (current)
	{
		toks = copy_toks(data, current);
		if (toks == NULL)
		{
			free_garbage(&data->garbage);
			exit(EXIT_FAILURE);
		}
		current->toks = toks;
		current = current->next;
	}
}

// FIXME should return the last value of child
int	prepare_command_forks(t_data *data)
{
	pid_t		*pids;
	size_t		cmd_count;
	size_t		count;

	if (!data || !data->command)
		return (-400);
	if (is_commands_valid(data) == 0)
		return (2);
	cmd_count = count_commands(data->command);
	fill_toks_into_commands(data, data->command);
	pids = malloc_gb(&data->garbage, sizeof(pid_t) * cmd_count);
	if (!pids)
	{
		free_garbage(&data->garbage);
		exit(EXIT_FAILURE);
	}
	count = 0;
	execute_pipeline(data, pids, &count);
	ignore_signal();
	wait_all_childs(data->command, pids);
	free_element_gb(&data->garbage, pids);
	signal_init();
	return (data->ret);
}
