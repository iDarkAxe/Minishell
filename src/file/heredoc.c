/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:41:09 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/17 09:08:03 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include "file.h"

// static void	heredoc_error(const char *delimitor);

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
			return (NULL);
		if (ft_strncmp(str, delimitor, ft_strlen(delimitor) + 1) == 0)
			break ;
		print_fd(tmp->fd, str);
		free(str);
		str = NULL;
		print_fd(tmp->fd, "\n");
	}
	if (str != NULL)
		free(str);
	if (close(tmp->fd) == -1)
	{
		print_fd(2, "Error closing heredoc file\n");
		return (NULL);
	}
	return (tmp->name);
}

// TODO Ajouter le heredoc error si on fait Ctrl+D

/**
 * @brief Specific error printing for heredoc
 * 
 * @param delimitor delimitor
 */
/* static void	heredoc_error(const char *delimitor)
{
	print_fd(2,
		"minishell: warning: here-doc delimited by end-of-file (wanted ");
	print_fd(2, delimitor);
	print_fd(2, ");\n");
} */
