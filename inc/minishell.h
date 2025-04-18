/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/09 13:37:38 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef PROMPT_MESSAGE_CUSTOM
#  define PROMPT_MESSAGE_CUSTOM 1
# endif

# define TMP_PATH "/tmp/"

# include "libft.h"
# include <stddef.h>

typedef struct s_tmp		t_tmp;
typedef struct s_file		t_file;
typedef struct s_command	t_command;

// typedef enum e_file_state	t_file_state;

enum						e_file_state
{
	FILE_IN = 0,
	FILE_OUT = 1
};

typedef struct s_tmp
{
	char					*name;
	int						fd;
}							t_tmp;

typedef struct s_file
{
	t_file					*next;
	char					*name;
	t_bool					parsed;
	t_bool					exist;
	t_bool					perm_read;
	t_bool					perm_write;
	t_bool					is_heredoc;
}							t_file;

typedef struct s_command
{
	char					*content;
	char					*command;
	t_file					*file_in;
	t_file					*file_out;
	t_bool					is_parsed;
	t_bool					is_executed;
}							t_command;

int							signal_init(void);
char						*get_prompt_message(void);
t_tmp						create_tmp(char *path, int nbr_try);

// File Management
int							build_files_redirection(t_command *command);
void						*add_file(t_command *command, unsigned int index,
								t_file **command_file);
int							build_files_data(t_command *command);
char						*ft_trim_word(char *str);
int							build_file_access(t_file *file);
t_file						*file_parser(t_file *file);

// Built-ins
int							ft_exit(char *str);
// int ft_exit(int number, char *str);

// DEBUGGING Functions
void						print_list_files(t_command *command);
void						print_perm_files(t_command *command);
#endif
