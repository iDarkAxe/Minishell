/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:52:27 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/26 11:52:40 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

static void	free_and_close(t_data *data)
{
	free_double_array(data->commands);
	close(data->fd.infile);
}

void	first_child(t_data *data, char *envp[], char *argv[])
{
	data->pid_1 = fork();
	if (data->pid_1 < 0)
	{
		free_and_close_all(data);
		exit(EXIT_SUCCESS);
	}
	if (data->pid_1 == 0)
	{
		if (dup2(data->fd.infile, STDIN_FILENO) == -1)
		{
			perror("");
			free_and_close_all(data);
			exit(EXIT_FAILURE);
		}
		if (dup2(data->fd.first_pipe[1], STDOUT_FILENO) == -1)
		{
			perror("");
			free_and_close_all(data);
			exit(EXIT_FAILURE);
		}
		close(data->fd.first_pipe[0]);
		exec_command(data, envp, argv[2]);
	}
	free_and_close(data);
}

void	last_child(t_data *data, char *envp[], char *argv[])
{
	data->pid_2 = fork();
	if (data->pid_2 < 0)
	{
		free_and_close_all(data);
		exit(EXIT_SUCCESS);
	}
	if (data->pid_2 == 0)
	{
		if (dup2(data->fd.first_pipe[0], STDIN_FILENO) == -1)
		{
			free_and_close_all(data);
			exit(EXIT_FAILURE);
		}
		if (dup2(data->fd.outfile, STDOUT_FILENO) == -1)
		{
			free_and_close_all(data);
			exit(EXIT_FAILURE);
		}
		close(data->fd.first_pipe[1]);
		exec_command(data, envp, argv[3]);
	}
}

void	one_conmmand(t_data *data, char *envp[], char *argv[])
{
	data->pid_1 = fork();
	if (data->pid_1 < 0)
	{
		free_and_close_all(data);
		exit(EXIT_SUCCESS);
	}
	if (data->pid_1 == 0)
	{
		if (dup2(data->fd.infile, STDIN_FILENO) == -1)
		{
			perror("");
			free_and_close_all(data);
			exit(EXIT_FAILURE);
		}
		if (dup2(data->fd.outfile, STDOUT_FILENO) == -1)
		{
			perror("");
			free_and_close_all(data);
			exit(EXIT_FAILURE);
		}
		close(data->fd.infile);
		exec_command(data, envp, argv[2]);
	}
	free_and_close(data);
}
