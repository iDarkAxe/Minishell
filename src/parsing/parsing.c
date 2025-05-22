/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:12:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/11 13:57:13 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "garbage.h"
#include "minishell.h"
#include "parsing.h"

size_t			count_without_quote(const char *str);

/**
 * @brief Prototype for parsing
 *
 * @param line line to parse
 * @return char**
 */
char	**parse_line(char *line)
{
	char	**tokens;

	// line = parsing_minishell(line);
	tokens = lexer(line);
	if (tokens == NULL)
	{
		free_element_gb(line);
		ft_exit((char *[]){"1", NULL});
	}
	free_element_gb(line);
	tokens = expand_tildes_tokens(tokens);
	if (tokens == NULL)
		ft_exit_int_np(1);
	return (tokens);
}

size_t	count_without_quote(const char *str)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (str && str[i])
	{
		if (quote != 0 && str[i] == quote)
			quote = 0;
		else if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else
			count++;
		i++;
	}
	return (count);
}

static t_bool	has_unclosed_quote(const char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (str && str[i])
	{
		if (quote != 0 && str[i] == quote)
			quote = 0;
		else if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		i++;
	}
	if (quote == 0)
		return (FALSE);
	return (TRUE);
}

// static char	*remove_quote(const char *str, char *new_str)
// {
// 	char	quote;
// 	size_t	i;
// 	size_t	j;
//
// 	i = 0;
// 	j = 0;
// 	quote = 0;
// 	while (str && str[i])
// 	{
// 		if (quote != 0 && str[i] == quote)
// 			quote = 0;
// 		else if (quote == 0 && (str[i] == '\"' || str[i] == '\''))
// 			quote = str[i];
// 		else
// 			new_str[j++] = str[i];
// 		i++;
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);
// }

static char *close_quote(const char *str, char *new_str, t_bool *have_to_expand)
{
	char	quote;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	quote = 0;
	while (str && str[i])
	{
		if (quote == str[i])
			quote = 0;
		else if (quote == 0 && str[i] == '\'')
		{
			quote = str[i];
			*have_to_expand = FALSE;
		}
		else if (quote == 0 && str[i] == '"')
		{
			quote = str[i];
			*have_to_expand = TRUE;
		}
		else
			new_str[j++] = str[i];
		i++;

	}
	new_str[j] = '\0';
	return (new_str);
}

char	*parsing_minishell(const char *str)
{
	char	*new_str;
	t_bool	*have_to_expand;
	char	*result;
	size_t	count;

	if (!str || has_unclosed_quote(str) == TRUE)
		return (NULL);
	have_to_expand = NULL;
	count = count_without_quote(str);
	new_str = malloc((count + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	*have_to_expand = FALSE;
	new_str = close_quote(str, new_str, have_to_expand);
	if (is_dollar(new_str) == TRUE && *have_to_expand == TRUE)
	{
		result = expand_variables_line(new_str);
	}
	else
	{
		result = new_str;
	}
	return (result);
}
