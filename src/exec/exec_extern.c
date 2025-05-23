/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/23 11:30:38 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

// TODO Ajouter la recherche de la commande dans le PATH

/**
 * @brief Executes commands that are not builtins
 *
 * @param command command structure
 * @param tokens array of strings
 * @return int
 */
int	not_builtins(t_data *data, t_command *command, char **tokens)
{
	char	*path;
	char	**toks;
	int		ret;

	if (tokens == NULL || tokens[0] == NULL)
		return (1);
	path = ft_strjoin("/usr/bin/", tokens[0]);
	if (path == NULL)
	{
		print_fd(2, "minishell: error on strjoin");
		ft_exit_int_np(1);
	}
	add_to_garbage(&data->garbage, path);
	toks = copy_toks(data, command);
	if (toks == NULL)
		return (-1);
	ret = execve_fork(data, path, toks, command->envp);
	return (ret);
}

int	execve_fork(t_data *data, char *path, char **toks, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		reset_signal_default();
		execve(path, toks, envp);
		perror("execve");
		free_garbage(&data->garbage);
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
			exit(126);
		else
			exit(1);
	}
	ignore_signal();
	waitpid(pid, &status, 0);
	free_element_gb(&data->garbage, path);
	free_array(&data->garbage, toks);
	signal_init();
	return ((status >> 8) & 0xFF);
}
