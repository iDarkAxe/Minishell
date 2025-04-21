/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/22 16:51:29 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef PROMPT_MESSAGE_CUSTOM
#  define PROMPT_MESSAGE_CUSTOM 1
# endif

# include "libft.h"
# include <stddef.h>

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

enum							e_file_state
{
	FILE_IN = 0,
	FILE_OUT = 1
};

struct							s_command
{
	struct s_command			*next;
	t_token						*tokens;
	char						*content;
	char						**envp;
	char						*command;
	t_bool						file_error;
	t_file						*file_in;
	t_file						*file_out;
	t_bool						is_parsed;
	t_bool						is_executed;
};

struct							s_env_vars
{
	t_var						*head_var;
	size_t						count;
};

struct							s_var
{
	t_var						*next;
	char						*value;
	t_params					*head_params;
	size_t						count;
};

struct							s_params
{
	t_params					*next;
	char						*value;
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

int								signal_init(void);
char							*get_prompt_message(void);

ssize_t							print_fd(int fd, const char *str);
ssize_t							printn_fd(int fd, const char *str, size_t len);

// Lexer
char							*ft_substr_end(char const *src,
									unsigned int start, size_t end);
int								is_operator_char(char c);
char							**lexer(const char *line);
t_command						*tokeniser(char **tokens, char **envp);

// Utils for manage memory
void							free_char_tokens(char **tokens);
void							free_command(t_command *command);
void							free_files_struct(t_file *file);
void							free_heredoc(t_tmp *tmp);
void							free_tokens(t_token *token);

// Built-ins
int								ft_exit(char **array);
int								ft_echo(char **array, char delimitor);

// DEBUGGING Functions
void							print_list_files(t_command *command);
void							print_perm_files(t_command *command);
ssize_t							print_command(t_command *command);

#endif
