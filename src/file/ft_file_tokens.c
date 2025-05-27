/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:35:32 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/26 16:27:09 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "garbage.h"
#include "minishell.h"

static t_token	*clean_tokens(t_token *head);
static int		is_redirection(char *str);
// static void		free_token(t_garbage *garbage, t_token *token);

/**
 * @brief Removes all the tokens of file redirections allready used
 *
 * @param data data structure
 * @return t_command*
 */
t_command	*remove_used_file_tokens(t_data *data)
{
	t_command	*current;

	current = data->command;
	while (current && current->tokens)
	{
		current->tokens = clean_tokens(current->tokens);
		current = current->next;
	}
	return (data->command);
}

/**
 * @brief Clean all tokens that are redirections
 *
 * @param head head of tokens
 * @return t_token*
 */
static t_token	*clean_tokens(t_token *head)
{
	t_token	*token;
	t_token	*prev;
	t_token	*next;

	token = head;
	prev = NULL;
	while (token && token->next)
	{
		if (is_redirection(token->str))
		{
			next = token->next->next;
			if (prev)
				prev->next = next;
			else
				head = next;
			token = next;
		}
		else
		{
			prev = token;
			token = token->next;
		}
	}
	return (head);
}

/**
 * @brief Check if str contain redirections signs
 *
 * @param str string to compare with redirections signs
 * @return int +,- or 0 values are redirections, 0 is not a redirection
 */
static int	is_redirection(char *str)
{
	return (!ft_strncmp(str, "<", 2) || !ft_strncmp(str, ">", 2)
		|| !ft_strncmp(str, "<<", 3) || !ft_strncmp(str, ">>", 3));
}

/**
 * @brief Free tokens of redirection with it's name
 *
 * @param token redirection sign token
 */
// static void	free_token(t_garbage *garbage, t_token *token)
// {
// 	if (token && token->str)
// 		free_element_gb(garbage, token->str);
// 	if (token && token->next && token->next->str)
// 		free_element_gb(garbage, token->next->str);
// 	if (token && token->next)
// 		free_element_gb(garbage, token->next);
// 	if (token)
// 		free_element_gb(garbage, token);
// 	token = NULL;
// }
