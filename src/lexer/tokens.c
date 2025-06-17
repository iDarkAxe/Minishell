/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:22:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/17 17:26:59 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "file.h"
#include "garbage.h"
#include "minishell.h"
#include "parsing.h"

static t_token		*create_token(t_garbage *garbage);
static t_command	*create_command(t_data *data);
static t_token		*iterate_token(t_garbage *garbage, char *str,
						t_token **token);
static t_command	*iterate_command(t_data *data, char *str,
						t_token **token, t_command **current);

/**
 * @brief Creates a t_command structure that contains all the tokens
 * Fills the command with the environment
 *
 * @param data data structure
 * @param tokens tokens
 * @return t_command* pointer if OK, NULL if it fails
 */
t_command	*tokeniser(t_data *data, char **tokens)
{
	t_command	*command;
	t_command	*current;
	t_token		*token;
	size_t		index;

	command = create_command(data);
	if (command == NULL)
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	current = command;
	token = command->tokens;
	index = 0;
	while (tokens && tokens[index] != NULL)
	{
		if (iterate_command(data, tokens[index], &token, &current) == NULL)
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		token->str = tokens[index];
		if (iterate_token(&data->garbage, tokens[index + 1], &token) == NULL)
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		index++;
	}
	return (command);
}

/**
 * @brief Create a token structure
 *
 * @return t_token* pointer if OK, NULL if it fails
 */
static t_token	*create_token(t_garbage *garbage)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (token == NULL)
		return (NULL);
	add_to_garbage(garbage, token);
	return (token);
}

/**
 * @brief Create a command structure
 *
 * @param data data structure
 * @return t_command* pointer if OK, NULL if it fails
 */
static t_command	*create_command(t_data *data)
{
	t_command	*command;

	command = ft_calloc(sizeof(t_command), 1);
	if (command == NULL)
		return (NULL);
	add_to_garbage(&data->garbage, command);
	command->tokens = create_token(&data->garbage);
	if (command->tokens == NULL)
	{
		free_element_gb(&data->garbage, command);
		return (NULL);
	}
	command->envp = env_to_array(data);
	command->fd[0] = 0;
	command->fd[1] = 1;
	return (command);
}

/**
 * @brief Makes iteration on the next token if the condition is completed
 *
 * @param str string
 * @param token token
 * @return t_token* pointer if OK, NULL if it fails
 */
static t_token	*iterate_token(t_garbage *garbage, char *str, t_token **token)
{
	t_token	*new_token;

	if (str && ft_strncmp(str, "|", 1) != 0)
	{
		new_token = create_token(garbage);
		if (new_token == NULL)
			return (NULL);
		(*token)->next = new_token;
		*token = (*token)->next;
	}
	return (*token);
}

/**
 * @brief  Makes iteration on the next token if the condition is completed
 * Creates a command in the process
 *
 * @param str str
 * @param token token
 * @param current command
 * @return t_command* pointer if OK, NULL if it fails
 */
static t_command	*iterate_command(t_data *data, char *str,
		t_token **token, t_command **current)
{
	if (str && ft_strncmp(str, "|", 1) == 0)
	{
		(*current)->next = create_command(data);
		if ((*current)->next == NULL)
			return (NULL);
		(*current) = (*current)->next;
		*token = (*current)->tokens;
	}
	return (*current);
}
