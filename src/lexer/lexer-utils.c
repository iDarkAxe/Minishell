/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:21 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/11 13:50:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int		is_operator_char(char c);
char	*ft_substr_end(char const *src, unsigned int start, size_t end);

/**
 * @brief Initialize the lexer structure
 *
 * Fill the structure with zeros and init the line to search in
 * and allocates the array to the garbage
 *
 * @param lex_st pointer to the lexer structure
 * @param line line to verify
 */
char	**init_lexer_state(t_lexer_state *lex_st, const char *line)
{
	ft_bzero(lex_st, sizeof(t_lexer_state));
	lex_st->line = line;
	lex_st->tokens = malloc(sizeof(char *) * MAX_TOKENS_LEX);
	if (lex_st->tokens == NULL)
		return (NULL);
	add_to_garbage(lex_st->tokens);
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
 * @param src source string
 * @param start start index to copy from
 * @param end end index to copy to
 * @return char* pointer to the new string
 */
char	*ft_substr_end(char const *src, unsigned int start, size_t end)
{
	size_t	len;
	char	*s;

	len = end - start;
	s = malloc_gb(len + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, &src[start], len);
	s[len] = '\0';
	return (s);
}
