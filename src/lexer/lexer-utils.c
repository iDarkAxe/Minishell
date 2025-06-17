/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:21 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/17 17:33:42 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "ft_printf.h"
#include <stdlib.h>

int		is_operator_char(char c);
char	*ft_substr_end_gb(t_garbage *garbage, char const *src,
			unsigned int start, size_t end);

/**
 * @brief Initialize the lexer structure
 *
 * Fill the structure with zeros and init the line to search in
 * and allocates the array to the garbage
 *
 * @param garbage garbage structure
 * @param lex_st pointer to the lexer structure
 * @param line line to verify
 */
char	**init_lexer_state(t_garbage *garbage, t_lexer_state *lex_st,
		const char *line)
{
	ft_bzero(lex_st, sizeof(t_lexer_state));
	lex_st->line = line;
	lex_st->tokens = ft_calloc(sizeof(char *), MAX_TOKENS_LEX);
	if (lex_st->tokens == NULL)
		return (NULL);
	add_to_garbage(garbage, lex_st->tokens);
	return (lex_st->tokens);
}

/**
 * @brief Is |, < or >
 *
 * @param c character to check
 * @return int 1 if c is operator, 0 otherwise
 */
int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * @brief Allocate memory for a string and copy the content from src
 *
 * @param garbage garbage structure
 * @param src source string
 * @param start start index to copy from
 * @param end end index to copy to
 * @return char* pointer to the new string
 */
char	*ft_substr_end_gb(t_garbage *garbage, char const *src,
		unsigned int start, size_t end)
{
	size_t	len;
	char	*s;

	len = end - start;
	s = malloc_gb(garbage, len + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, &src[start], len);
	s[len] = '\0';
	return (s);
}

/**
 * @brief Verify that current token doesn't exceed MAX_TOKEN_LEX value
 * 
 * @param lexer lexer structure
 * @return int 0 ok, error otherwise 
 */
int	verify_token_number(t_garbage *garbage, t_lexer_state *lexer)
{
	if (!lexer)
		return (1);
	if (lexer->token_limit_exceeded == 1)
		return (2);
	if (lexer->j >= MAX_TOKENS_LEX - 1)
	{
		lexer->token_limit_exceeded = 1;
		free_array(garbage, lexer->tokens);
		lexer->tokens = NULL;
		ft_dprintf(2, "Error: token limit exceeded : %d\n", MAX_TOKENS_LEX);
		return (3);
	}
	return (0);
}
