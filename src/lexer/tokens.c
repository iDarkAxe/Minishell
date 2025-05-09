/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:22:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/09 16:36:24 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "garbage.h"
#include "file.h"
#include "builtins.h"

static t_token		*create_token(void);
static t_command	*create_command(char **envp);
static t_token		*iterate_token(char *str, t_token **token);
static t_command	*iterate_command(char *str, t_token **token,
						t_command **current);

/**
 * @brief Creates a t_command structure that contains all the tokens
 * Fills the command with the environment
 * 
 * @param tokens tokens
 * @param envp environment
 * @return t_command* pointer if OK, NULL if it fails
 */
t_command	*tokeniser(char **tokens, char **envp)
{
	t_command	*command;
	t_command	*current;
	t_token		*token;
	size_t		index;

	command = create_command(envp);
	if (command == NULL)
		ft_exit_int_np(1);
	current = command;
	token = command->tokens;
	index = 0;
	while (tokens && tokens[index] != NULL)
	{
		if (iterate_command(tokens[index], &token, &current) == NULL)
			ft_exit_int_np(1);
		token->str = tokens[index];
		if (iterate_token(tokens[index + 1], &token) == NULL)
			ft_exit_int_np(1);
		index++;
	}
	return (command);
}

/**
 * @brief Create a token structure
 * 
 * @return t_token* pointer if OK, NULL if it fails
 */
static t_token	*create_token(void)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (token == NULL)
		return (NULL);
	add_to_garbage(token);
	return (token);
}

/**
 * @brief Create a command structure
 * 
 * @param envp environment
 * @return t_command* pointer if OK, NULL if it fails
 */
static t_command	*create_command(char **envp)
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
	command->envp = envp;
	fd_default(command);
	return (command);
}

/**
 * @brief Makes iteration on the next token if the condition is completed
 * 
 * @param str string
 * @param token token
 * @return t_token* pointer if OK, NULL if it fails
 */
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

/**
 * @brief  Makes iteration on the next token if the condition is completed
 * Creates a command in the process
 * 
 * @param str str
 * @param token token
 * @param current command
 * @return t_command* pointer if OK, NULL if it fails
 */
static t_command	*iterate_command(char *str, t_token **token,
		t_command **current)
{
	if (str && ft_strncmp(str, "|", 1) == 0)
	{
		(*current)->next = create_command((*current)->envp);
		if ((*current)->next == NULL)
			return (NULL);
		(*current) = (*current)->next;
		*token = (*current)->tokens;
	}
	return (*current);
}
