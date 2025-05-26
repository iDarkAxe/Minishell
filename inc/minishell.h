/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/26 18:14:01 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef PROMPT_MESSAGE_CUSTOM
#  define PROMPT_MESSAGE_CUSTOM 1
# endif

# ifndef FOLLOW_ZSH
#  define FOLLOW_ZSH 0
# endif

# include "data_structure.h"
# include "libft.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int			minishell(t_data *data, char **envp);
int			is_interactive(void);
int			short_minishell_no_tty(t_data *data, char **envp);

int			signal_init(void);
void		reset_signal_default(void);
void		ignore_signal(void);
char		*get_prompt_message(t_garbage *garbage);

// Printing
ssize_t		print_fd(int fd, const char *str);
ssize_t		printn_fd(int fd, const char *str, size_t len);
void		print_command_fd(t_command *command);

// Lexer
char		*ft_substr_end_gb(t_garbage *garbage, char const *src,
				unsigned int start, size_t end);
int			is_operator_char(char c);
char		**init_lexer_state(t_garbage *garbage, t_lexer_state *lex_st,
				const char *line);
char		**lexer(t_garbage *garbage, const char *line);
t_command	*tokeniser(t_garbage *garbage, char **tokens, char **envp);

// Parsing
char		**parse_line(t_garbage *garbage, char *line);
char		**expand_tildes_tokens(t_garbage *garbage, char **tokens);

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
// void							change_input_of_pipe(t_command *command,
// t_bool in_out);
int			needs_to_be_forked(t_command *command);
int			execve_fork(t_data *data, char *path, char **toks, char **envp);
int			create_pipe(t_command *command);
int			handle_redirections_forks(t_garbage *garbage, t_command *command);

// EXEC UTILS
size_t		count_commands(t_command *command);
void		safe_close(int *fd);
void		dup_and_close(t_garbage *garbage, int oldfd, int newfd);

void		execute_pipeline(t_data *data, pid_t *pids, size_t *count);
size_t		count_commands(t_command *command);
void		fill_toks_into_commands(t_data *data, t_command *command);
void		search_path(t_data *data, t_command *command);
void		search_paths(t_data *data, t_command *command);
void		wait_all_childs(t_command *command, pid_t *pids);

// Utils for manage memory
void		free_array(t_garbage *garbage, char **array);
void		free_command(t_garbage *garbage, t_command *command);
void		free_files_struct(t_garbage *garbage, t_file *file);
void		free_heredoc(t_garbage *garbage, t_tmp *tmp);
void		free_tokens(t_garbage *garbage, t_token *token);

// Utils for export
int			check_args_export(const char *str);

// Utils for env
void		print_env(t_env_vars *env);

// DEBUGGING Functions
void		print_list_files(t_command *command);
void		print_perm_files(t_command *command);
ssize_t		print_command(t_command *command);
ssize_t		print_commands(t_command *command);

// Utils
t_bool		is_dollar(char *str);

#endif
