/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>        +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:12:50 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/05 13:08:08 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "garbage.h"
#include "ft_printf.h"
#include "minishell.h"
#include "parsing.h"

static char	**remove_quote_tokens(t_data *data, char **tokens);

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

	tokens = lexer(&data->garbage, line);
	if (tokens == NULL)
	{
		free_element_gb(&data->garbage, line);
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
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
