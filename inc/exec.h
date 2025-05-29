/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/29 10:59:27 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "data_structure.h"

// Exec
char		**copy_toks(t_data *data, t_command *command);
void		print_toks(char **tokens);
int			prepare_command(t_data *data);
int			prepare_command_forks(t_data *data);
int			search_command(t_data *data, t_command *command, char **tokens);
int			not_builtins(t_data *data, t_command *command, char **tokens);
int			handle_redirections(t_garbage *garbage, t_command *command,
				int fd_backup[2]);
void		reset_redirection(t_garbage *garbage, t_command *command,
				int fd_backup[2],
				unsigned char i);
int			needs_to_be_forked(t_command *command);
int			execve_fork(t_data *data, char *path, char **toks, char **envp);
int			create_pipe(t_command *command);
int			handle_redirections_forks(t_garbage *garbage, t_command *command);

// EXEC UTILS
size_t		count_commands(t_command *command);
int			safe_close(int *fd);
void		dup_and_close(t_garbage *garbage, int oldfd, int newfd);

void		execute_pipeline(t_data *data, pid_t *pids, size_t *count);
size_t		count_commands(t_command *command);
void		fill_toks_into_commands(t_data *data, t_command *command);
void		search_path(t_data *data, t_command *command);
void		search_paths(t_data *data, t_command *command);
void		wait_all_childs(t_command *command, pid_t *pids);

#endif
