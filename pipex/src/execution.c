/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:31:36 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/06 16:11:11 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_with_path(t_data *data, char *command);

char	*get_command_with_path(t_data *data, char *command)
{
	data->i = 0;
	while (data->all_paths[data->i])
	{
		data->commands = ft_split(command, ' ');
		if (!data->commands)
			return (NULL);
		data->path_bin = str_two_join(data->all_paths[data->i], "/",
				data->commands[0]);
		if (!data->path_bin)
		{
			free_double_array(data->commands);
			exit(EXIT_FAILURE);
		}
		if (access(data->path_bin, X_OK) == -1)
		{
			free(data->path_bin);
			data->i++;
		}
		else
			return (data->path_bin);
		free_double_array(data->commands);
	}
	return (NULL);
}

static void	check_if_absolute_path(t_data *data, char *pathname)
{
	char	*is_path;

	is_path = ft_strchr(pathname, '/');
	if (is_path != NULL || data->path_is_empty == TRUE)
	{
		if (access(pathname, X_OK) == -1 || data->path_is_empty == TRUE)
		{
			close(data->fd.outfile);
			ft_putstr_fd(pathname, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}

static void	handle_absolute_path(t_data *data, char *pathname, char *command,
		char *envp[])
{
	char	**final_command;
	char	*temp;

	final_command = malloc(sizeof(char *) * 3);
	temp = ft_strrchr(command, '/') + 1;
	final_command[1] = ft_strdup(temp);
	final_command[2] = NULL;
	if (!final_command)
	{
		free_and_close_all(data);
		exit(EXIT_FAILURE);
	}
	free_double_array(data->commands);
	if (execve(pathname, &final_command[1], envp) == -1)
	{
		free_double_array(final_command);
		free_and_close_all(data);
		exit(EXIT_FAILURE);
	}
	free_double_array(final_command);
}

void	exec_command(t_data *data, char *envp[], char *command)
{
	data->pathname = command;
	check_if_absolute_path(data, data->pathname);
	if (access(data->pathname, X_OK) == -1)
	{
		data->pathname = get_command_with_path(data, command);
		if (!data->pathname)
		{
			free_and_close_all(data);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		if (execve(data->pathname, data->commands, envp) == -1)
		{
			free_and_close_all(data);
			exit(EXIT_FAILURE);
		}
		free_and_close_all(data);
	}
	else
		handle_absolute_path(data, data->pathname, command, envp);
}
