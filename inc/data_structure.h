/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:19:09 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/17 10:29:40 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURE_H
# define DATA_STRUCTURE_H

# include "libft.h"
# include "garbage.h"
# include "env.h"

// FROM file.h
typedef struct s_tmp			t_tmp;
typedef struct s_file			t_file;

// FROM garbage.h
typedef struct s_element		t_element;
typedef struct s_garbage		t_garbage;

// FROM env.h
typedef struct s_env_vars		t_env_vars;
typedef struct s_var			t_var;

// For lexer.c
typedef struct s_lexer_state	t_lexer_state;

typedef struct s_command		t_command;
typedef struct s_params			t_params;
typedef struct s_token			t_token;
typedef struct s_data			t_data;

/**
 * @brief General structure that have access to all needed in minishell
 * 
 */
struct							s_data
{
	t_garbage					garbage;
	t_env_vars					env;
	t_command					*command;
	int							ret;
	char						*last_token;
};

/**
 * @brief Structure that handles all the command and there contents
 * 
 */
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
	t_bool						file_error;
	t_bool						parse_error;
	int							return_value;
};

/**
 * @brief Basic structure of linked list of strings
 * 
 */
struct							s_token
{
	char						*str;
	struct s_token				*next;
};

/**
 * @defgroup Lexer Lexer structure
 * @brief Core functionality of the lexer.
 * @{
 */
# ifndef MAX_TOKENS_LEX
#  define MAX_TOKENS_LEX 1024
# endif

/**
 * @brief Structure used by lexer to efficiently 
 * have access to a bunch of variables
 * 
 */
struct							s_lexer_state
{
	unsigned int				i;
	unsigned int				j;
	unsigned int				start;
	t_bool						token_limit_exceeded;
	t_bool						in_single_quote;
	t_bool						in_double_quote;
	char						**tokens;
	const char					*line;
};
/** @} */

#endif
