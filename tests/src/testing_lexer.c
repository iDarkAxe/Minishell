/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:16:13 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/11 16:37:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "unity.h"
#include "unity_internals.h"

void	print_array(char **array);

void	print_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		printf("Token[i] == %s\n", array[i]);
		i++;
	}
}

void	lexer_simple(void)
{
	char	*line;
	char	**tokens;
	char	**verif;
	int		i;

	line = "cat \"'my file.txt'\" | gr\"ep\" hello >> out.txt";
	verif = (char *[]){"cat", "\"'my file.txt'\"", "|", "gr\"ep\"", "hello",
		">>", "out.txt"};
	tokens = lexer(line);
	i = 0;
	while (tokens[i] != NULL)
	{
		TEST_ASSERT_EQUAL_STRING(verif[i], tokens[i]);
		i++;
	}
	free_garbage();
}
