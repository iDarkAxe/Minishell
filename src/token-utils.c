/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:22:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/22 11:29:41 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include <stdio.h>

static size_t	count_tokens(t_token const *head);
static char		**fill_toks(t_token *head, char **tokens);

char	**copy_toks(t_command *command)
{
	t_token	*token;
	char	**tokens;

	if (!command || !command->tokens)
		return (NULL);
	tokens = malloc(sizeof(char *) * (count_tokens(command->tokens) + 1));
	if (!tokens)
		return (NULL);
	token = command->tokens;
	if (token->str != NULL && ft_strncmp(token->str, "|", 2) == 0)
		token = token->next;
	fill_toks(token, tokens);
	return (tokens);
}

void	print_toks(char **tokens)
{
	size_t	index;

	index = 0;
	while (tokens != NULL && tokens[index] != NULL)
	{
		printf("toks %zu : %s\n", index, tokens[index]);
		index++;
	}
}

static void	free_strs(char **strs)
{
	size_t	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free_element_gb(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free_element_gb(strs);
	strs = NULL;
}

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

static char	**fill_toks(t_token *head, char **tokens)
{
	size_t	i;
	t_token	*temp;

	i = 0;
	if (head == NULL || head->str == NULL || head == NULL)
		return (NULL);
	temp = head;
	while (temp != NULL && temp->str != NULL)
	{
		tokens[i] = ft_strdup(temp->str);
		if (!tokens[i])
		{
			free_strs(tokens);
			return (NULL);
		}
		add_to_garbage(tokens[i]);
		i++;
		temp = temp->next;
	}
	tokens[i] = NULL;
	return (tokens);
}
