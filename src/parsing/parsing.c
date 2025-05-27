/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:12:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/27 16:23:58 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "garbage.h"
#include "builtins.h"
#include "minishell.h"

// FIXME Removed parsing_minishell as it was crashing instantly
// line = parsing_minishell(line);
/**
 * @brief Prototype for parsing
 *
 * @param line line to parse
 * @return char**
 */
char	**parse_line(t_data *data, char *line)
{
	char	**tokens;

	line = setup_string(data, line);
	if (!line)
		return (NULL);
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
	return (tokens);
}
