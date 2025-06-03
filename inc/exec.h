/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/03 16:19:38 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "data_structure.h"

/**
 * @defgroup Exec Exec Functions
 * @brief Main functions for executing a command
 * @{
 */
char		**copy_toks(t_data *data, t_command *command);
int			prepare_command(t_data *data);
int			prepare_command_forks(t_data *data);
int			simple_search_command(t_data *data, t_command *command,
				const char *cmd);
int			search_command(t_data *data, t_command *command, char **tokens);
int			not_builtins(t_data *data, t_command *command, char **tokens);
int			handle_redirections(t_garbage *garbage, t_command *command,
				int fd_backup[2]);
void		reset_redirection(t_garbage *garbage, t_command *command,
				int fd_backup[2],
				unsigned char i);
int			needs_to_be_forked(t_command *command);
int			execve_fork(t_data *data, char *path, char **toks, char **envp);
int			handle_redirections_forks(t_garbage *garbage, t_command *command);
/** @} */

/**
 * @defgroup Exec-utils Exec Utils
 * @brief Functions used in exec that are simple utils
 * @{
 */
size_t		count_commands(t_command *command);
int			safe_close(int *fd);
void		dup_and_close(t_garbage *garbage, int oldfd, int newfd);

void		execute_pipeline(t_data *data, pid_t *pids, size_t *count);
size_t		count_commands(t_command *command);
void		fill_toks_into_commands(t_data *data, t_command *command);
void		search_paths(t_data *data, t_command *command);
void		wait_all_childs(t_command *command, pid_t *pids);
/** @} */

#endif
