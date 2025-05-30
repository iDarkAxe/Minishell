/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:41:09 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/30 11:24:22 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "garbage.h"
#include "exec.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>

static void	heredoc_error(const char *delimitor);
static int	fill_heredoc(t_garbage *garbage, t_file *file);

/**
 * @brief Read from stdin and outputs to a file,
 * stops reading when Ctrl+D or when a delimitor is found
 *
 * @param tmp structure for heredocs
 * @param delimitor string to know when to stop reading
 * @return char* tmp->name if successful, NULL otherwise
 */
char	*read_heredoc(t_tmp *tmp, char *delimitor)
{
	char	*str;

	while (1)
	{
		str = readline("heredoc> ");
		if (str == NULL)
		{
			heredoc_error(delimitor);
			return (tmp->name);
		}
		if (ft_strncmp(str, delimitor, ft_strlen(delimitor) + 1) == 0)
			break ;
		ft_dprintf(tmp->fd, str);
		free(str);
		str = NULL;
		ft_dprintf(tmp->fd, "\n");
	}
	if (str != NULL)
		free(str);
	safe_close(&tmp->fd);
	tmp->fd = open(tmp->name, O_RDONLY, 0644);
	if (tmp->fd < 0)
		perror("minishell: heredoc: open 2nd time");
	return (tmp->name);
}

/**
 * @brief Specific error printing for heredoc
 *
 * @param delimitor delimitor
 */
static void	heredoc_error(const char *delimitor)
{
	ft_dprintf(2,
		"minishell: warning: here-doc delimited by end-of-file (wanted ");
	ft_dprintf(2, delimitor);
	ft_dprintf(2, ");\n");
}

/**
 * @brief Fill the heredoc if it's one
 *
 * @param file file struct
 * @return int 1 OK, 0 or less error
 */
static int	fill_heredoc(t_garbage *garbage, t_file *file)
{
	if (file == NULL)
		return (0);
	if (file->is_heredoc != 1)
		return (1);
	file->tmp = malloc_gb(garbage, sizeof(t_tmp) * 1);
	if (file->tmp == NULL)
		return (-1);
	*file->tmp = create_tmp(garbage, TMP_PATH, 3);
	if (file->tmp->fd == -1)
	{
		free_element_gb(garbage, file->tmp);
		ft_dprintf(2, "Error: tmp file creation\n");
		return (-1);
	}
	read_heredoc(file->tmp, file->name);
	return (1);
}

/**
 * @brief Fill all the heredocs in the correct order
 *
 * @param garbage garbage structure
 * @param command command structure
 * @return int 0 OK, otherwise error
 */
int	fill_heredocs(t_garbage *garbage, t_command *command)
{
	t_command	*current;
	t_file		*cur_file;
	t_file		*last_file;

	if (command == NULL)
		return (1);
	if (command->file_error == 1)
		return (0);
	last_file = NULL;
	current = command;
	while (current)
	{
		cur_file = current->file_in;
		while (cur_file != NULL)
		{
			cur_file = search_last_file(current->file_in, last_file);
			last_file = cur_file;
			if (fill_heredoc(garbage, cur_file) == -1)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
