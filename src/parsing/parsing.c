/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:53:12 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/26 18:08:54 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "garbage.h"
#include "builtins.h"
#include "minishell.h"

/**
 * @brief Prototype for parsing
 *
 * @param line line to parse
 * @return char**
 */
char	**parse_line(char *line)
{
	char	**tokens;

	line = setup_string(line);
	if (!line)
		return (NULL);
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
