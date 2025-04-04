/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/04 13:12:37 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef PROMPT_MESSAGE_CUSTOM
#  define PROMPT_MESSAGE_CUSTOM 1
# endif

# define TMP_PATH "/tmp/"

# include "libft.h"

typedef struct s_tmp		t_tmp;
typedef struct s_file		t_file;
typedef struct s_command	t_command;
typedef struct s_env_vars	t_env_vars;
typedef struct s_params		t_params;

struct						s_tmp
{
	char					*name;
	int						fd;
};

struct						s_file
{
	t_file					*next;
	char					*name;
	t_bool					parsed;
	t_bool					exist;
	t_bool					perm_read;
	t_bool					perm_write;
	t_bool					is_heredoc;
};

struct						s_command
{
	char					*content;
	char					*command;
	t_file					*file_in;
	t_file					*file_out;
	t_bool					is_parsed;
	t_bool					is_executed;
};

struct						s_env_vars
{
	t_element				*head_elem;
	size_t					count;
};

struct						s_element
{
	t_element				*next;
	char					*value;
	t_params				*head_params;
	size_t					count;
};

struct						s_params
{
	t_params				*next;
	char					*value;
};

int							signal_init(void);
char						*get_prompt_message(void);
t_tmp						create_tmp(char *path, int nbr_try);

#endif
