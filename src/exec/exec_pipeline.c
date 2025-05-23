/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:23:30 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/23 11:43:12 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

static void	execve_exit(int value)__attribute__((noreturn));
static void	execute_command_from_pipe(t_data *data, t_command *command,
				int pipefd[2], int prev_fd, int ret);

/**
 * @brief Execute the command from pipe
 *
 * @param command command structure
 * @param pipefd fds of pipe
 * @param prev_fd fd of previous command
 * @param ret ret value of previous command
 */
static void	execute_command_from_pipe(t_data *data, t_command *command,
		int pipefd[2], int prev_fd, int ret)
{
	int	value;

	if (!data || command == NULL || pipefd == NULL)
		return ;
	reset_signal_default();
	if (prev_fd != -1)
		dup_and_close(&data->garbage, prev_fd, 0);
	if (command->next)
	{
		safe_close(&pipefd[0]);
		dup_and_close(&data->garbage, pipefd[1], 1);
	}
	if (handle_redirections_forks(command) != 0 || command->file_error != 0)
	{
		free_garbage(&data->garbage);
		exit(0);
	}
	value = search_command(data, command, command->toks, ret);
	if (value != 0)
		execve(command->path, command->toks, command->envp);
	if (value != 0)
		perror("minishell: execve");
	free_garbage(&data->garbage);
	execve_exit(value);
}

/**
 * @brief Execute all the command that are followed by pipes
 *
 * @param data data structure
 * @param pids array of pids of childs
 * @param ret ret value of previous command
 */
void	execute_pipeline(t_data *data, pid_t *pids, int ret)
{
	int			pipefd[2];
	int			prev_fd;
	int			i;
	t_command	*current;

	if (!data)
		return ;
	prev_fd = -1;
	i = 0;
	current = data->command;
	while (current && pids)
	{
		if (current->next)
			pipe(pipefd);
		pids[i] = fork();
		if (pids[i] == 0)
			execute_command_from_pipe(data, current, pipefd, prev_fd, ret);
		safe_close(&prev_fd);
		if (current->next)
		{
			safe_close(&pipefd[1]);
			prev_fd = pipefd[0];
		}
		current = current->next;
		i++;
	}
	safe_close(&prev_fd);
}

/**
 * @brief Waits for all the childs with their pids
 *
 * @param command command structure
 * @param pids array of pids of childs
 */
void	wait_all_childs(t_command *command, pid_t *pids)
{
	size_t		nbr_cmds;
	size_t		index;
	t_command	*current;
	int			wstatus;

	if (pids == NULL)
		return ;
	nbr_cmds = count_commands(command);
	index = 0;
	current = command;
	while (index < nbr_cmds && current)
	{
		if (waitpid(pids[index], &wstatus, 0) == -1)
			perror("waitpid");
		if (WIFEXITED(wstatus))
			current->return_value = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			current->return_value = 128 + WTERMSIG(wstatus);
		index++;
		current = current->next;
	}
}

/**
 * @brief Specific exit for execve and builtins in forks
 *
 */
static void	execve_exit(int value)
{
	if (value == 0)
		exit(0);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES)
		exit(126);
	else
		exit(1);
}
