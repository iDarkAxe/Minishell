/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:49:27 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/10 11:32:14 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "pipex.h"
#include "parsing.h"
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*parsing_minishell(const char *str)
{
	char *temp;
	char *new_str;

	temp = string_pre_cleaning(str);
	if (!temp)
		return (NULL);
	new_str = clean_string(temp);
	if (!new_str)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (new_str);
}

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*str;
	char	*result;

	// str = "simple"; // sans quote
	str = "'simple'"; // quote simple bien fermée
	// str = "\"simple\""; // quote double bien fermée
	// str = "'simple"; // quote simple non fermée
	// str = "\"simple"; // quote double non fermée
	// str = "\"in 'the' middle\""; // quotes imbriquées
	// str = "'in \"the\" middle'"; // quotes imbriquées inversées
	// str = "\"   spaced string   \""; // quote avec espaces internes
	// str = "   \"trimmed\"   "; // quote bien fermée avec espaces autour
	// str = ""; // chaîne vide
	// str = "    "; // que des espaces
	// str = "'\"'"; // quote simple contenant une quote double
	// str = "\"'\""; // quote double contenant une quote simple
	// str = "word \"another word\""; // mot + string entre quote

	result = parsing_minishell(str);
	if (result)
	{
		printf("✅ [%s]\n", result);
		free(result);
	}
	else
		printf("❌ Parsing error or NULL result\n");

	return (0);
}
