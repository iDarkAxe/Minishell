/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/22 17:16:30 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "libft.h"
# include "minishell.h"

# define TMP_PATH "/tmp/"

typedef struct s_tmp			t_tmp;
typedef struct s_file			t_file;

struct							s_tmp
{
	char						*name;
	int							fd;
};

struct							s_file
{
	t_file						*next;
	char						*name;
	t_tmp						*tmp;
	t_bool						parsed;
	t_bool						exist;
	t_bool						perm_read;
	t_bool						perm_write;
	t_bool						is_heredoc;
	t_bool						is_append;
};

int								files_management(t_command *command);

// File Management
int								build_files_redirection(t_command *command);
void							*add_file(t_command *command, t_token *token,
									t_file **command_file);
int								build_files_data(t_command *command);
t_command						*remove_used_file_tokens(t_command *command);
t_tmp							create_tmp(char *path, int nbr_try);
char							*ft_trim_word(char *str);
int								build_file_access(t_file *file);
t_file							*file_parser(t_file *file);
char							*read_heredoc(t_tmp *tmp, char *delimiteur);

#endif
