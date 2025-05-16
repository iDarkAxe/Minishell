/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/09 16:20:48 by ppontet          ###   ########lyon.fr   */
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

# ifndef MAX_TOKENS_LEX
#  define MAX_TOKENS_LEX 1024
# endif

# include "libft.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// FROM file.h
typedef struct s_tmp			t_tmp;
typedef struct s_file			t_file;

// FROM garbage.h
typedef struct s_element		t_element;
typedef struct s_garbage		t_garbage;

typedef struct s_command		t_command;
typedef struct s_var			t_var;
typedef struct s_env_vars		t_env_vars;
typedef struct s_params			t_params;
typedef struct s_lexer_state	t_lexer_state;
typedef struct s_token			t_token;

struct							s_command
{
	struct s_command			*next;
	t_token						*tokens;
	char						**toks;
	char						*path;
	char						**envp;
	t_file						*file_in;
	t_file						*file_out;
	int							fd[2];
	int							fd_backup[2];
	t_bool						file_error;
	t_bool						parse_error;
	int							return_value;
};

struct							s_lexer_state
{
	unsigned int				i;
	unsigned int				j;
	unsigned int				start;
	t_bool						in_single_quote;
	t_bool						in_double_quote;
	char						**tokens;
	const char					*line;
};

struct							s_token
{
	char						*str;
	struct s_token				*next;
};

int								minishell(char **envp);
int								read_context(char **envp);
void							short_minishell_no_tty(char **envp);

int								signal_init(void);
void							reset_signal_default(void);
void							ignore_signal(void);
char							*get_prompt_message(void);

// Printing
ssize_t							print_fd(int fd, const char *str);
ssize_t							printn_fd(int fd, const char *str, size_t len);
void							print_command_fd(t_command *command);

// Lexer
char							*ft_substr_end(char const *src,
									unsigned int start, size_t end);
int								is_operator_char(char c);
char							**init_lexer_state(t_lexer_state *lex_st,
									const char *line);
char							**lexer(const char *line);
t_command						*tokeniser(char **tokens, char **envp);

// Parsing
char							**parse_line(char *line);
char							**expand_tildes_tokens(char **tokens);

// Exec
char							**copy_toks(t_command *command);
void							print_toks(char **tokens);
int								prepare_command(t_command *command, int ret);
int								prepare_command_forks(t_command *command,
									int ret);
int								search_command(t_command *command,
									char **tokens, int ret);
int								not_builtins(t_command *command, char **tokens);
int								handle_redirections(t_command *command);
void							reset_redirection(t_command *command,
									unsigned char i);
// void							change_input_of_pipe(t_command *command,
// t_bool in_out);
int								needs_to_be_forked(t_command *command);
int								execve_fork(char *path, char **toks,
									char **envp);
int								create_pipe(t_command *command);
int								handle_redirections_forks(t_command *command);

// EXEC UTILS
size_t							count_commands(t_command *command);
void							safe_close(int *fd);
void							dup_and_close(int oldfd, int newfd);

void							execute_pipeline(t_command *command,
									pid_t *pids, int ret);
size_t							count_commands(t_command *command);
void							fill_toks_into_commands(t_command *command);
void							search_paths(t_command *command);
void							wait_all_childs(t_command *command,
									pid_t *pids);

// Utils for manage memory
void							free_array(char **array);
void							free_command(t_command *command);
void							free_files_struct(t_file *file);
void							free_heredoc(t_tmp *tmp);
void							free_tokens(t_token *token);

// Utils for export
void							print_export(t_env_vars *env);
int								check_args_export(const char *str);

// Utils for env
void							print_env(t_env_vars *env);

// DEBUGGING Functions
void							print_list_files(t_command *command);
void							print_perm_files(t_command *command);
ssize_t							print_command(t_command *command);
ssize_t							print_commands(t_command *command);

// Utils
t_bool	is_dollar(char *str);

#endif
