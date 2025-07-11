/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:22:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/13 15:19:13 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"

static size_t	count_tokens(t_token const *head);
static char		**fill_toks(t_garbage *garbage, t_token *head, char **tokens);
char			**copy_toks(t_data *data, t_command *command);

/**
 * @brief Creates a copy of all tokens that are in a command structure
 * It's used for forks during exec
 *
 * @param data data structure
 * @param command command structure
 * @return char** copy of tokens
 */
char	**copy_toks(t_data *data, t_command *command)
{
	t_token	*token;
	char	**tokens;
	size_t	count;

	if (!command)
		return (NULL);
	token = command->tokens;
	if (token && token->str != NULL && ft_strncmp(token->str, "|", 2) == 0)
		token = token->next;
	count = count_tokens(token);
	tokens = malloc_gb(&data->garbage, sizeof(char *) * (count + 1));
	if (count == 0)
	{
		tokens[0] = NULL;
		return (tokens);
	}
	fill_toks(&data->garbage, token, tokens);
	return (tokens);
}

/**
 * @brief Count how many tokens are in a linked list of t_token structure
 *
 * @param head start of linked list
 * @return size_t number of t_token structs
 */
static size_t	count_tokens(t_token const *head)
{
	size_t			count;
	t_token const	*temp;

	if (head == NULL)
		return (0);
	count = 0;
	temp = head;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

/**
 * @brief Creates effectively the copy of the t_token structure to char **array
 *
 * @param head start of linked list
 * @param tokens array of strings to copy to
 * @return char**
 */
static char	**fill_toks(t_garbage *garbage, t_token *head, char **tokens)
{
	size_t	i;
	t_token	*temp;

	i = 0;
	if (head == NULL || head->str == NULL || head == NULL)
		return (NULL);
	temp = head;
	tokens[0] = NULL;
	while (temp != NULL && temp->str != NULL)
	{
		tokens[i] = ft_strdup(temp->str);
		if (!tokens[i])
		{
			free_array(garbage, tokens);
			return (NULL);
		}
		add_to_garbage(garbage, tokens[i]);
		i++;
		temp = temp->next;
	}
	tokens[i] = NULL;
	return (tokens);
}
