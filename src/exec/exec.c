/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:35:28 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/06 16:48:31 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "garbage.h"
#include "builtins.h"

static void	store_restore_fds(t_bool store);

/**
 * @brief Prepare the command for search_command()
 *
 * @param command command structure
 * @return int
 */
int	prepare_command(t_command *command, int ret)
{
	char		**toks;

	if (!command)
		ft_exit_int(1);
	print_command(command);
	toks = copy_toks(command);
	if (toks == NULL)
		ft_exit_int(1);
	handle_redirections(command);
	if (command->file_error != 1 && search_command(command, toks,
			ret) != 0)
		command->return_value = not_builtins(command, toks);
	free_array(toks);
	if (command->fd[0] != 0)
		close(command->fd[0]);
	if (command->fd[1] != 1)
		close(command->fd[1]);
	return (command->return_value);
}

int	prepare_command_forks(t_command *command, int ret)
{
	t_command	*current;
	char		**toks;

	if (!command)
		ft_exit_int(1);
	store_restore_fds(0);
	current = command;
	while (current != NULL)
	{
		print_command(current);
		toks = copy_toks(current);
		if (toks == NULL)
			ft_exit_int(1);
		create_pipe(command);
		handle_redirections(current);
		if (current->file_error != 1)
			executes_in_forks(current, toks, ret);
		ret = current->return_value;
		free_array(toks);
		current = current->next;
	}
	store_restore_fds(1);
	return (ret);
}

/**
 * @brief Store and restore file descriptor of stdin and stdout
 * 
 * @param store 0 = STORE, 1 = RESTORE
 */
static void	store_restore_fds(t_bool store)
{
	static int	fd[2] = {0, 1};

	if (store == 0)
	{
		fd[0] = dup(0);
		fd[1] = dup(1);
	}
	else
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		fd[0] = 0;
		fd[1] = 1;
	}
}
