/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/18 12:27:15 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "exec.h"
#include <errno.h>

#include <sys/wait.h>
#include "ft_printf.h"
#include <string.h>

/**
 * @brief Executes commands that are not builtins
 *
 * @param data data structure
 * @param command command structure
 * @param tokens array of strings
 * @return int
 */
int	not_builtins(t_data *data, t_command *command, char **tokens)
{
	int		ret;

	if (tokens == NULL || tokens[0] == NULL)
		return (1);
	ret = execve_fork(data, command->path, command->toks, command->envp);
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
		status = errno;
		ft_dprintf(2, "minishell: %s: %s\n", path, strerror(status));
		free_garbage(&data->garbage);
		if (status == ENOENT)
			exit(127);
		else if (status == EACCES)
			exit(126);
		else
			exit(1);
	}
	ignore_signal();
	waitpid(pid, &status, 0);
	signal_init();
	return (evaluate_status_code_as_ret(status));
}
