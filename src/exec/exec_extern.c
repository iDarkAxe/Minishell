/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/30 11:49:24 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

static int	execve_fork(char *path, char **toks, char **envp);

// TODO Ajouter la recherche de la commande dans le PATH

/**
 * @brief Executes commands that are not builtins
 *
 * @param command command structure
 * @param tokens array of strings
 * @return int
 */
int	not_builtins(t_command *command, char **tokens)
{
	char	*path;
	char	**toks;
	int		ret;

	if (tokens == NULL || tokens[0] == NULL)
		return (1);
	path = ft_strjoin("/usr/bin/", tokens[0]);
	if (path == NULL)
		ft_exit_int(1);
	add_to_garbage(path);
	toks = copy_toks(command);
	if (toks == NULL)
		return (-1);
	ret = execve_fork(path, toks, command->envp);
	return (ret);
}

static int	execve_fork(char *path, char **toks, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		reset_signal_default();
		execve(path, toks, envp);
		perror("execve");
		if (errno == ENOENT)
			ft_exit_int(127);
		else if (errno == EACCES)
			ft_exit_int(126);
		else
			ft_exit_int(1);
	}
	ignore_signal();
	waitpid(pid, &status, 0);
	free_element_gb(path);
	free_array(toks);
	signal_init();
	return ((status >> 8) & 0xFF);
}
