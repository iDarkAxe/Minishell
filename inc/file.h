/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/17 14:06:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "libft.h"
# include "minishell.h"

# define TMP_PATH "/tmp/"

typedef struct s_tmp	t_tmp;
typedef struct s_file	t_file;

/**
 * @brief Basic structure to help manipulating heredocs (tmp file)
 *
 */
struct					s_tmp
{
	char				*name;
	int					fd;
};

/**
 * @brief Structure to handle all the data of a file
 *
 */
struct					s_file
{
	t_file				*next;
	char				*name;
	t_tmp				*tmp;
	t_bool				parsed;
	t_bool				exist;
	t_bool				perm_read;
	t_bool				perm_write;
	t_bool				is_heredoc;
	t_bool				is_append;
};

/**
 * @defgroup Files Files functions
 * @brief Function to manipulate files
 * @{
 */
int						files_management(t_data *data);

int						build_files_redirection(t_data *data);
void					*add_file(t_garbage *garbage, t_command *command,
							t_token *token, t_file **command_file);
int						build_files_data(t_command *command);
t_command				*remove_used_file_tokens(t_data *data);
int						build_file_access(t_file *file);
t_file					*file_parser(t_file *file);
t_tmp					create_tmp(t_garbage *garbage, char *path, int nbr_try);
char					*read_heredoc(t_tmp *tmp, char *delimitor);
int						verify_access(t_garbage *garbage, t_command *command);
t_file					*search_last_file(t_file *file,
							t_file *already_searched);
int						fill_heredocs(t_garbage *garbage, t_command *command);
int						open_file_with_rights(t_garbage *garbage, t_file *file,
							t_bool in_out);
void					read_write_to(t_garbage *garbage, t_command *command,
							t_bool in_out);
/** @} */
#endif
