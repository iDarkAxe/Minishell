/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/29 11:40:25 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef PROMPT_MESSAGE_CUSTOM
#  define PROMPT_MESSAGE_CUSTOM 1
# endif

/**
 * @brief Follow certain added functionnality of ZSH to minishell
 * 
 * 
 */
# ifndef FOLLOW_ZSH
#  define FOLLOW_ZSH 1
# endif

# include "data_structure.h"
# include "libft.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <wait.h>

int			minishell(t_data *data);
int			is_interactive(void);
int			short_minishell_no_tty(t_data *data);

int			signal_init(void);
void		reset_signal_default(void);
void		ignore_signal(void);
char		*get_prompt_message(t_garbage *garbage);

// Printing
ssize_t		print_fd(int fd, const char *str);
ssize_t		printn_fd(int fd, const char *str, size_t len);
void		print_command_fd(t_command *command);

// Lexer
char		**init_lexer_state(t_garbage *garbage, t_lexer_state *lex_st,
				const char *line);
char		**lexer(t_garbage *garbage, const char *line);
t_command	*tokeniser(t_data *data, char **tokens);
char		*ft_substr_end_gb(t_garbage *garbage, char const *src,
				unsigned int start, size_t end);
int			is_operator_char(char c);

// Parsing
char		**parse_line(t_data *data, char *line);
char		**expand_tildes_tokens(t_garbage *garbage, char **tokens);

// Utils for manage memory
void		free_array(t_garbage *garbage, char **array);
void		free_command(t_garbage *garbage, t_command *command);
void		free_commands(t_garbage *garbage, t_command **command);
void		free_files_struct(t_garbage *garbage, t_file *file);
void		free_heredoc(t_garbage *garbage, t_tmp *tmp);
void		free_tokens(t_garbage *garbage, t_token *token);

// DEBUGGING Functions
void		print_list_files(t_command *command);
void		print_perm_files(t_command *command);
void		print_toks(char **tokens);
ssize_t		print_command(t_command *command);
ssize_t		print_commands(t_command **command);

#endif
