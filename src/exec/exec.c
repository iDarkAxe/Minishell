/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/26 18:14:27 by ppontet          ###   ########lyon.fr   */
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
 * @param data data structure
 * @return int
 */
int	prepare_command(t_data *data)
{
	char	**toks;
	int		fd[2];

	if (!data || !data->command)
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	toks = copy_toks(data, data->command);
	if (toks == NULL)
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	handle_redirections(&data->garbage, data->command, fd);
	if (data->command->file_error != 1 && search_command(data, data->command,
			toks) != 0)
		data->command->return_value = not_builtins(data, data->command, toks);
	free_array(&data->garbage, toks);
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

// FIXME IT"S ONLY A PLACEHOLDER DON'T BE CONFUSED
void	search_path(t_data *data, t_command *command)
{
	t_command	*current;

	current = command;
	while (current)
	{
		if (!command->toks || !command->toks[0])
			command->path = "NULL";
		else
			command->path = ft_strjoin("/usr/bin/", command->toks[0]);
		if (command->path == NULL)
		{
			free_garbage(&data->garbage);
			exit(EXIT_FAILURE);
		}
		add_to_garbage(&data->garbage, command->path);
		command = command->next;
	}
}

// FIXME IT"S ONLY A PLACEHOLDER DON'T BE CONFUSED
void	search_paths(t_data *data, t_command *command)
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
			free_garbage(&data->garbage);
			exit(EXIT_FAILURE);
		}
		add_to_garbage(&data->garbage, current->path);
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
	cmd_count = count_commands(data->command);
	fill_toks_into_commands(data, data->command);
	search_paths(data, data->command);
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
