/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/13 14:29:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**
 * @brief Make the prompt custom (with colors)
 * 
 * looks like : "$USER@$(hostname):$(pwd)$
 * colors :	- user and hostname + ':'
 *			- current working directory
 *
 */
# ifndef PROMPT_MESSAGE_CUSTOM
#  define PROMPT_MESSAGE_CUSTOM 1
# endif

/**
 * @brief Follow certain added functionnality of ZSH to minishell
 * 
 */
# ifndef FOLLOW_ZSH
#  define FOLLOW_ZSH 0
# endif

# include "data_structure.h"
# include "libft.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <wait.h>

/**
 * @defgroup Basics Basic functions
 * @brief Basics functions to execute a minishell properly
 * @{
 */
int			minishell(t_data *data);
int			is_interactive(void);
int			minishell_no_tty(t_data *data);
char		*get_prompt_message(t_garbage *garbage);
/** @} */

/**
 * @defgroup Signal Signal functions
 * @brief Functions used for signal handling for the main thread and its childs
 * @{
 */
int			signal_init(void);
void		reset_signal_default(void);
void		ignore_signal(void);
/** @} */

/**
 * @defgroup Lexer Lexer functions
 * @brief Functions to make a correct use of lexing and tokenisation
 * @{
 */
char		**init_lexer_state(t_garbage *garbage, t_lexer_state *lex_st,
				const char *line);
int			verify_token_number(t_garbage *garbage, t_lexer_state *lexer);
char		**lexer(t_garbage *garbage, const char *line);
t_command	*tokeniser(t_data *data, char **tokens);
char		*ft_substr_end_gb(t_garbage *garbage, char const *src,
				unsigned int start, size_t end);
int			is_operator_char(char c);
/** @} */

/**
 * @defgroup Parsing Parsing Functions
 * @brief Functions to make parsing efficient
 * @{
 */
char		**parse_line(t_data *data, char *line);
t_bool		is_commands_valid(t_data *data);
/** @} */

/**
 * @defgroup Memory Memory Management
 * @brief Functions to free the allocated memory when it's not needed anymore
 * @{
 */
void		free_array(t_garbage *garbage, char **array);
void		free_command(t_garbage *garbage, t_command *command);
void		free_commands(t_garbage *garbage, t_command **command);
void		free_files_struct(t_garbage *garbage, t_file *file);
void		free_heredoc(t_garbage *garbage, t_tmp *tmp);
void		free_tokens(t_garbage *garbage, t_token *token);
/** @} */

/**
 * @defgroup Debug Debug Functions
 * @brief Functions to help debugging faster
 * @{
 */
void		print_list_files(t_command *command);
void		print_perm_files(t_command *command);
void		print_tokens(t_token *tokens);
void		print_toks(char **toks);
void		print_alltoks(t_command *command);
void		print_alltokens(t_command *command);
ssize_t		print_command(t_command *command);
ssize_t		print_commands(t_command **command);
/** @} */

#endif
