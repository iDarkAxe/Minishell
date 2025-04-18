/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:22:09 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/18 11:19:48 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include <stddef.h>

static char	is_all_same_letter(char *str, char tested);
static char	handle_options(char **array, size_t *index);
int			ft_echo(char **array, char delimitor);

/**
 * @brief Echo with -n option
 * Delimitor is the character to print between tokens
 * OPTIONS :
 *  -n : print without the triling newline
 * 
 * NOTES : you can add any number of n after -n if you want
 * 
 * @param array array of strings
 * @param delimitor character to delimit arrays
 * @return int 
 */
int	ft_echo(char **array, char delimitor)
{
	size_t	index;
	char	final_n;

	index = 0;
	final_n = 1;
	final_n = handle_options(array, &index);
	while (array != NULL && array[index] != NULL)
	{
		print_fd(1, array[index]);
		if (array[index + 1] != NULL)
			printn_fd(1, &delimitor, 1);
		index++;
	}
	if (final_n == 1)
		print_fd(1, "\n");
	return (0);
}

/**
 * @brief Verify that all the letters are only the same as the tested
 * 
 * @param str string to search letters
 * @param tested character to compare
 * @return char 0 if at least one char is different, 1 otherwise
 */
static char	is_all_same_letter(char *str, const char tested)
{
	size_t	index;

	index = 0;
	while (str && str[index] != '\0')
	{
		if (str[index] != tested)
			return (0);
		index++;
	}
	return (1);
}

/**
 * @brief Handle the options, and increments the starting point of tokens
 * 
 * @param array array of strings
 * @param index index
 * @return char 1 no options found, 0 if at least one option found
 */
static char	handle_options(char **array, size_t *index)
{
	char	opt_not_found;
	size_t	j;

	j = 0;
	opt_not_found = 1;
	while (array != NULL && array[j] != NULL)
	{
		if (array[j][0] == '-' && is_all_same_letter(&array[j][1], 'n') == 1)
		{
			opt_not_found = 0;
			*index = j + 1;
		}
		else
			break ;
		j++;
	}
	return (opt_not_found);
}

// // READLINE
// #include <readline/history.h>
// #include <readline/readline.h>
// #include <stdio.h>
// // OTHER
// #include "garbage.h"
// #include "libft.h"
// #include "minishell.h"
// #include <stdlib.h>
// #include <unistd.h>
// #include "file.h"

// void	files_management(t_command *command);

// int	ft_echo(char **array, char delimitor);

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*line;
// 	char		**tokens;
// 	t_command	*command;

// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	line = readline("mini_echo> ");
// 	if (line == NULL || line[0] == '\0')
// 		ft_exit((char *[]){"1", NULL});
// 	add_to_garbage(line);
// 	tokens = lexer(line);
// 	if (tokens == NULL)
// 		ft_exit((char *[]){"1", NULL});
// 	command = tokeniser(tokens);
// 	if (!command)
// 		ft_exit((char *[]){"1", NULL});
// 	// print_command(command);
// 	ft_echo(&tokens[0], ' ');
// 	free_command(command);
// 	free_garbage();
// 	return (0);
// }