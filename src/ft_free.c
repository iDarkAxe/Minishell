/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:41:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/16 18:04:07 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"

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
		free_element_gb(temp);
		temp = next;
	}
}

void	free_char_tokens(char **tokens)
{
	size_t	index;

	index = 0;
	while (tokens && tokens[index])
	{
		free_element_gb(tokens[index]);
		tokens[index] = NULL;
		index++;
	}
	free_element_gb(tokens);
}

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
		free_element_gb(temp);
		temp = next;
	}
	free_element_gb(token);
	token = NULL;
}

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

void	free_heredoc(t_tmp *tmp)
{
	if (tmp == NULL)
		return ;
	if (tmp->name != NULL && access(tmp->name, F_OK) == 0)
	{
		close(tmp->fd);
		unlink(tmp->name);
		free_element_gb(tmp->name);
	}
	free_element_gb(tmp);
}
