/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:26:12 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/21 09:31:06 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	error_message(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

static void	initialize_values(t_data *data)
{
	data->all_paths = NULL;
	data->commands = NULL;
	data->path = NULL;
	data->path_bin = NULL;
	data->pathname = NULL;
	data->path_is_empty = FALSE;
	data->fd.outfile = -1;
	data->fd.infile = -1;
	data->fd.first_pipe[0] = -1;
	data->fd.first_pipe[1] = -1;
}

static void	fds_pipes(t_data *data, char *argv[], int argc, char *envp[])
{
	data->fd.outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd.outfile == -1)
		error_message(argv[4]);
	data->fd.infile = open(argv[1], O_RDONLY, 0644);
	if (data->fd.infile == -1)
	{
		error_message(argv[2]);
		close(data->fd.outfile);
		exit(EXIT_SUCCESS);
	}
	if (pipe(data->fd.first_pipe) == -1)
	{
		perror("");
		close(data->fd.outfile);
		close(data->fd.infile);
		exit(EXIT_FAILURE);
	}
	data->all_paths = get_path_bins(data, envp);
	if (!data->all_paths)
		data->all_paths = NULL;
}

static void	handle_return_of_status(t_data data, int argc)
{
	if (waitpid(data.pid_1, &data.status, 0) == -1)
		exit(EXIT_FAILURE);
	if (data.status == 127)
		exit(127);
	if (data.status == -1)
		exit(EXIT_FAILURE);
	if (argc > 4 && waitpid(data.pid_2, &data.status, 0) == -1)
		exit(EXIT_FAILURE);
	if (argc > 4 && data.status == -1)
		exit(EXIT_FAILURE);
	if (argc > 4 && data.status == 127)
		exit(127);
	if (WIFEXITED(data.status))
		exit(WEXITSTATUS(data.status));
	else if (WIFSIGNALED(data.status))
		exit(128 + WTERMSIG(data.status));
}

int	exec(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 3 || argc > 5)
		return (EXIT_SUCCESS);
	initialize_values(&data);
	fds_pipes(&data, argv, argc, envp);
	if (argc > 4)
	{
		first_child(&data, envp, argv);
		close(data.fd.first_pipe[1]);
		last_child(&data, envp, argv);
		close(data.fd.first_pipe[0]);
		free_and_close_all(&data);
	}
	else if (argc == 4)
	{
		one_conmmand(&data, envp, argv);
		free_and_close_all(&data);
	}
	free_and_close_all(&data);
	handle_return_of_status(data, argc);
	return (EXIT_SUCCESS);
}
