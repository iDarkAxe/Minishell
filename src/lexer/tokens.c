/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:22:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/15 10:48:14 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"

static t_token		*create_token(void);
static t_command	*create_command(void);
static t_token		*iterate_token(char *str, t_token **token);
static t_command	*iterate_command(char *str, t_token **token,
						t_command **current);

t_command	*tokeniser(char **tokens)
{
	t_command	*command;
	t_command	*current;
	t_token		*token;
	size_t		index;

	command = create_command();
	if (command == NULL)
		return (NULL);
	current = command;
	token = command->tokens;
	index = 0;
	while (tokens && tokens[index] != NULL)
	{
		if (iterate_command(tokens[index], &token, &current) == NULL)
			return (NULL);
		token->str = tokens[index];
		if (iterate_token(tokens[index + 1], &token) == NULL)
			return (NULL);
		index++;
	}
	return (command);
}

static t_token	*create_token(void)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (token == NULL)
		return (NULL);
	add_to_garbage(token);
	return (token);
}

static t_command	*create_command(void)
{
	t_command	*command;

	command = ft_calloc(sizeof(t_command), 1);
	if (command == NULL)
		return (NULL);
	add_to_garbage(command);
	command->tokens = create_token();
	if (command->tokens == NULL)
	{
		free_element_gb(command);
		return (NULL);
	}
	return (command);
}

static t_token	*iterate_token(char *str, t_token **token)
{
	t_token	*new_token;

	if (str && ft_strncmp(str, "|", 1) != 0)
	{
		new_token = create_token();
		if (new_token == NULL)
			return (NULL);
		(*token)->next = new_token;
		*token = (*token)->next;
	}
	return (*token);
}

static t_command	*iterate_command(char *str, t_token **token,
		t_command **current)
{
	if (str && ft_strncmp(str, "|", 1) == 0)
	{
		(*current)->next = create_command();
		if ((*current)->next == NULL)
			return (NULL);
		(*current) = (*current)->next;
		*token = (*current)->tokens;
	}
	return (*current);
}
