/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:12:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/03 12:04:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "garbage.h"
#include "builtins.h"

/**
 * @brief Prototype for parsing
 *
 * @param line line to parse
 * @return char**
 */
char	**parse_line(char *line)
{
	char	**tokens;

	tokens = lexer(line);
	if (tokens == NULL)
	{
		free_element_gb(line);
		ft_exit((char *[]){"1", NULL});
	}
	free_element_gb(line);
	tokens = expand_tildes_tokens(tokens);
	if (tokens == NULL)
		ft_exit_int(1);
	return (tokens);
}
