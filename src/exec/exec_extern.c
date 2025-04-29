/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/29 17:03:39 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

static void	execve_fork(char *path, char **toks, char **envp);

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

	if (tokens == NULL || tokens[0] == NULL)
		return (1);
	path = ft_strjoin("/usr/bin/", tokens[0]);
	if (path == NULL)
		ft_exit((char *[]){"1", NULL});
	add_to_garbage(path);
	toks = copy_toks(command);
	if (toks == NULL)
		return (-1);
	execve_fork(path, toks, command->envp);
	return (0);
}

static void	execve_fork(char *path, char **toks, char **envp)
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
			ft_exit((char *[]){"127", NULL});
		else if (errno == EACCES)
			ft_exit((char *[]){"126", NULL});
		else
			ft_exit((char *[]){"1", NULL});
	}
	ignore_signal();
	waitpid(pid, &status, 0);
	free_element_gb(path);
	free_array(toks);
	signal_init();
	if (WIFEXITED(status))
		set_return_value((status >> 8) & 0xFF);
}
