/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:12:50 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 15:57:29 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"
#include "garbage.h"
#include "minishell.h"
#include "parsing.h"

static char	**remove_quote_tokens(t_data *data, char **tokens);

static void	check_errors_quotes(char *str, char *quote)
{
	if (*quote == '0' && *str == '"')
		*quote = *str;
	else if (*quote == '0' && *str == '\'')
		*quote = *str;
	else if (*quote == *str)
		*quote = '0';
	str++;
	if (*str == '\0')
		return ;
	check_errors_quotes(str, quote);
}

char	*setup_string(t_data *data, char *str)
{
	char	*str_expanded;
	char	*result;
	char	quote;

	result = NULL;
	quote = 0;
	str_expanded = expand_str(data, str);
	free_element_gb(&data->garbage, str);
	if (!str_expanded)
		return (NULL);
	add_to_garbage(&data->garbage, str_expanded);
	if (detect_quote(str_expanded) == FALSE)
		return (str_expanded);
	result = remove_quote(data, str_expanded, &quote);
	if (!result)
		return (NULL);
	add_to_garbage(&data->garbage, result);
	return (result);
}

/**
 * @brief Prototype for parsing
 *
 * @param data data structure
 * @param line line to parse
 * @return char**
 */
char	**parse_line(t_data *data, char *line)
{
	char	**tokens;
	char	quote;

	quote = '0';
	check_errors_quotes(line, &quote);
	if (quote != '0')
	{
		ft_dprintf(2, "minishell: syntax error: Unclosed quote: `%c'\n", quote);
		return (NULL);
	}
	tokens = lexer(&data->garbage, line);
	if (tokens == NULL)
	{
		data->ret = 2;
		return (NULL);
	}
	free_element_gb(&data->garbage, line);
	tokens = expand_tildes_tokens(&data->garbage, tokens);
	if (tokens == NULL)
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	tokens = remove_quote_tokens(data, tokens);
	if (tokens == NULL)
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	return (tokens);
}

static char	**remove_quote_tokens(t_data *data, char **tokens)
{
	size_t	index;

	if (tokens == NULL || tokens[0] == NULL)
		return (NULL);
	index = 0;
	while (tokens[index] != NULL)
	{
		tokens[index] = setup_string(data, tokens[index]);
		if (tokens[index] == NULL)
			tokens[index] = ft_strdup_gb(&data->garbage, "");
		if (tokens[index] == NULL)
		{
			ft_dprintf(2,
				"minishell: malloc: Critical error of malloc, exiting.\n");
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		}
		index++;
	}
	return (tokens);
}
