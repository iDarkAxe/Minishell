/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/30 11:25:56 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "garbage.h"
#include "minishell.h"

/**
 * @brief Free one t_command structure with all that it contains
 *
 * @param garbage garbage structure
 * @param command t_command structure
 */
void	free_command(t_garbage *garbage, t_command *command)
{
	t_command	*next;

	next = command->next;
	if (command->file_in != NULL)
		free_files_struct(garbage, command->file_in);
	if (command->file_out != NULL)
		free_files_struct(garbage, command->file_out);
	if (command->tokens != NULL)
		free_tokens(garbage, command->tokens);
	ft_bzero(command, sizeof(t_command));
	free_element_gb(garbage, command);
	command = next;
}

/**
 * @brief Free t_command linked list structure with all that it contains
 *
 * @param garbage garbage structure
 * @param command head of t_command linked list structure
 */
void	free_commands(t_garbage *garbage, t_command **command)
{
	t_command	*temp;
	t_command	*next;

	temp = *command;
	while (temp != NULL)
	{
		next = temp->next;
		free_command(garbage, temp);
		temp = next;
	}
	*command = NULL;
}

/**
 * @brief Free t_tokens linked list structure
 *
 * @param garbage garbage structure
 * @param token head of t_tokens linked list structure
 */
void	free_tokens(t_garbage *garbage, t_token *token)
{
	t_token	*temp;
	t_token	*next;

	temp = token;
	while (temp != NULL)
	{
		if (temp->str != NULL)
		{
			free_element_gb(garbage, temp->str);
			temp->str = NULL;
		}
		next = temp->next;
		ft_bzero(temp, sizeof(t_token));
		free_element_gb(garbage, temp);
		temp = NULL;
		temp = next;
	}
	free_element_gb(garbage, token);
	token = NULL;
}

/**
 * @brief Free linked list of t_file structure
 *
 * @param garbage garbage structure
 * @param file head of t_file linked list structure
 */
void	free_files_struct(t_garbage *garbage, t_file *file)
{
	t_file	*temp;
	t_file	*next;

	if (file == NULL)
		return ;
	temp = file;
	while (temp != NULL)
	{
		if (temp->tmp != NULL)
			free_heredoc(garbage, temp->tmp);
		if (temp->name != NULL)
		{
			free_element_gb(garbage, temp->name);
			temp->name = NULL;
		}
		next = temp->next;
		free_element_gb(garbage, temp);
		temp = next;
	}
}

/**
 * @brief Free heredoc structure
 *
 * @param garbage garbage structure
 * @param tmp heredoc structure
 */
void	free_heredoc(t_garbage *garbage, t_tmp *tmp)
{
	if (tmp == NULL)
		return ;
	if (tmp->name != NULL && access(tmp->name, F_OK) == 0)
	{
		close(tmp->fd);
		unlink(tmp->name);
		free_element_gb(garbage, tmp->name);
		tmp->name = NULL;
	}
	free_element_gb(garbage, tmp);
	tmp = NULL;
}
