/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/28 12:35:14 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "garbage.h"
#include "minishell.h"

/**
 * @brief Free t_command linked list structure with all that it contains
 *
 * @param command head of t_command linked list structure
 */
void	free_command(t_command *command)
{
	t_command	*temp;
	t_command	*next;

	temp = command;
	while (temp != NULL)
	{
		if (temp->file_in != NULL)
			free_files_struct(temp->file_in);
		if (temp->file_out != NULL)
			free_files_struct(temp->file_out);
		if (temp->tokens != NULL)
			free_tokens(temp->tokens);
		next = temp->next;
		ft_bzero(temp, sizeof(t_command));
		free_element_gb(temp);
		temp = next;
	}
}

/**
 * @brief Free array of strings
 *
 * @param array array of strings
 */
void	free_array(char **array)
{
	size_t	index;

	if (array == NULL)
		return ;
	index = 0;
	while (array && array[index])
	{
		free_element_gb(array[index]);
		array[index] = NULL;
		index++;
	}
	free_element_gb(array);
	array = NULL;
}

/**
 * @brief Free t_tokens linked list structure
 *
 * @param token head of t_tokens linked list structure
 */
void	free_tokens(t_token *token)
{
	t_token	*temp;
	t_token	*next;

	temp = token;
	while (temp != NULL)
	{
		if (temp->str != NULL)
		{
			free_element_gb(temp->str);
			temp->str = NULL;
		}
		next = temp->next;
		ft_bzero(temp, sizeof(t_token));
		free_element_gb(temp);
		temp = NULL;
		temp = next;
	}
	free_element_gb(token);
	token = NULL;
}

/**
 * @brief Free linked list of t_file structure
 *
 * @param file head of t_file linked list structure
 */
void	free_files_struct(t_file *file)
{
	t_file	*temp;
	t_file	*next;

	if (file == NULL)
		return ;
	temp = file;
	while (temp != NULL)
	{
		if (temp->tmp != NULL)
			free_heredoc(temp->tmp);
		if (temp->name != NULL)
		{
			free_element_gb(temp->name);
			temp->name = NULL;
		}
		next = temp->next;
		free_element_gb(temp);
		temp = next;
	}
}

/**
 * @brief Free heredoc structure
 *
 * @param tmp heredoc structure
 */
void	free_heredoc(t_tmp *tmp)
{
	if (tmp == NULL)
		return ;
	if (tmp->name != NULL && access(tmp->name, F_OK) == 0)
	{
		close(tmp->fd);
		unlink(tmp->name);
		free_element_gb(tmp->name);
		tmp->name = NULL;
	}
	free_element_gb(tmp);
	tmp = NULL;
}
