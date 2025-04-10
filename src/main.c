/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/10 15:58:05 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// READLINE
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
// OTHER
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "pipex.h"
#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*str;
// 	char	*prompt;
//
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	signal_init();
// 	prompt = get_prompt_message();
// 	if (prompt == NULL)
// 	{
// 		free_garbage();
// 		write(2, "Error creating prompt\n", 22);
// 		exit(1);
// 	}
// 	str = readline(prompt);
// 	if (str == NULL)
// 		return (-1);
// 	add_history(str);
// 	add_to_garbage(str);
// 	free_garbage();
// }

char	*parsing_minishell(const char *str);

int	main(void)
{
	const char	*str;
	char	*result;

	// str = "simple"; // sans quote
	// str = "'simple'"; // quote simple bien fermée
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
	str = "wo\"r\"d";

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
