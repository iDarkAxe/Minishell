/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:17:23 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/24 16:45:43 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#define MAX_TOKENS 1024

static char	**init_lexer_state(t_lexer_state *lex_st, const char *line);
static void	handle_space(t_lexer_state *lex_st);
static void	handle_quote(t_lexer_state *lex_st, char quote_type);
static void	handle_operator(t_lexer_state *lex_st);

/**
 * @brief Create tokens (small chunks) a line with the quotes and operators
 *
 * Handle spaces, quotes (' and ') and shell operator (|, <, <<, >, >>).
 * Return an array of tokens (strings), NULL terminated.
 *
 * @param line line to tokenise
 * @return Array of strings
 */
char	**lexer(const char *line)
{
	t_lexer_state	lex_st;

	if (init_lexer_state(&lex_st, line) == NULL)
		return (NULL);
	while (lex_st.line[lex_st.i] != '\0')
	{
		if (ft_isspace(lex_st.line[lex_st.i]) && !lex_st.in_single_quote
			&& !lex_st.in_double_quote)
			handle_space(&lex_st);
		else if ((lex_st.line[lex_st.i] == '\''
				|| lex_st.line[lex_st.i] == '"'))
			handle_quote(&lex_st, lex_st.line[lex_st.i]);
		else if (is_operator_char(lex_st.line[lex_st.i])
			&& !lex_st.in_single_quote && !lex_st.in_double_quote)
			handle_operator(&lex_st);
		else
			lex_st.i++;
	}
	if (lex_st.start < lex_st.i)
		lex_st.tokens[lex_st.j++] = ft_substr_end(lex_st.line, lex_st.start,
				lex_st.i);
	lex_st.tokens[lex_st.j] = NULL;
	return (lex_st.tokens);
}

/**
 * @brief Initialize the lexer structure
 *
 * Fill the structure with zeros and init the line to search in
 * and allocates the array to the garbage
 *
 * @param lex_st pointer to the lexer structure
 * @param line line to verify
 */
static char	**init_lexer_state(t_lexer_state *lex_st, const char *line)
{
	ft_bzero(lex_st, sizeof(t_lexer_state));
	lex_st->line = line;
	lex_st->tokens = malloc(sizeof(char *) * MAX_TOKENS);
	if (lex_st->tokens == NULL)
		return (NULL);
	add_to_garbage(lex_st->tokens);
	return (lex_st->tokens);
}

/**
 * @brief Handle the case where a space is found outside quotes
 *
 * Ends the current token if it exist and ignore the successive whitespaces,
 * and update to the next token
 *
 * @param lex_st pointer to the lexer structure
 */
static void	handle_space(t_lexer_state *lex_st)
{
	if (lex_st->start < lex_st->i)
		lex_st->tokens[lex_st->j++] = ft_substr_end(lex_st->line, lex_st->start,
				lex_st->i);
	lex_st->i++;
	while (ft_isspace(lex_st->line[lex_st->i]))
		lex_st->i++;
	lex_st->start = lex_st->i;
}

/**
 * @brief Handle the opening/closing of quotes (even/odd)
 *
 * Enable or disable the state of the quote if it's single or double
 * at the condition that it's not already in another type of quote
 *
 * @param lex_st pointer to the lexer structure
 * @param quote_type quote searched (' or ")
 */
static void	handle_quote(t_lexer_state *lex_st, char quote_type)
{
	if (quote_type == '\'' && !lex_st->in_double_quote)
		lex_st->in_single_quote = !lex_st->in_single_quote;
	else if (quote_type == '"' && !lex_st->in_single_quote)
		lex_st->in_double_quote = !lex_st->in_double_quote;
	lex_st->i++;
}

/**
 * @brief Handle the shell operators like |, <, >, << and >>.
 *
 * Cuts the current token if it exist, exctract the operator,
 * handle the double operators (<< and >>),
 * skips the following spaces and update to the next token
 *
 * @param lex_st pointer to the lexer structure
 */
static void	handle_operator(t_lexer_state *lex_st)
{
	if (lex_st->start < lex_st->i)
		lex_st->tokens[lex_st->j++] = ft_substr_end(lex_st->line, lex_st->start,
				lex_st->i);
	if ((lex_st->line[lex_st->i] == '<' || lex_st->line[lex_st->i] == '>')
		&& lex_st->line[lex_st->i + 1] == lex_st->line[lex_st->i])
	{
		lex_st->tokens[lex_st->j++] = ft_substr_end(lex_st->line, lex_st->i,
				lex_st->i + 2);
		lex_st->i += 2;
	}
	else
	{
		lex_st->tokens[lex_st->j++] = ft_substr_end(lex_st->line, lex_st->i,
				lex_st->i + 1);
		lex_st->i++;
	}
	while (ft_isspace(lex_st->line[lex_st->i]))
		lex_st->i++;
	lex_st->start = lex_st->i;
}
