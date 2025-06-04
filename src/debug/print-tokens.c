/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print-tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:22:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/02 17:24:17 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include <stdio.h>

/**
 * @brief Print toks indexed
 *
 * @param toks toks to print
 */
void	print_toks(char **toks)
{
	size_t	index;

	if (toks == NULL)
	{
		printf("No toks to print\n");
		return ;
	}
	index = 0;
	while (toks[index] != NULL)
	{
		printf("toks %zu : %s\n", index, toks[index]);
		index++;
	}
}

/**
 * @brief Print tokens indexed
 *
 * @param tokens tokens to print
 */
void	print_tokens(t_token *tokens)
{
	t_token	*head;
	size_t	index;

	if (tokens == NULL)
	{
		printf("No toks to print\n");
		return ;
	}
	head = tokens;
	index = 0;
	while (head != NULL)
	{
		printf("tokens %zu : %s\n", index, head->str);
		index++;
		head = head->next;
	}
}

/**
 * @brief Print all toks indexed
 *
 * @param command command structure
 */
void	print_alltoks(t_command *command)
{
	t_command	*current;

	if (command == NULL)
	{
		printf("No toks to print\n");
		return ;
	}
	current = command;
	while (current != NULL)
	{
		print_toks(current->toks);
		current = current->next;
	}
}

/**
 * @brief Print all tokens indexed
 *
 * @param command command structure
 */
void	print_alltokens(t_command *command)
{
	t_command	*current;

	if (command == NULL)
	{
		printf("No tokens to print\n");
		return ;
	}
	current = command;
	while (current != NULL)
	{
		print_tokens(current->tokens);
		current = current->next;
	}
}
