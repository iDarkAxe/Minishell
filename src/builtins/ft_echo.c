/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:22:09 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/09 16:29:22 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include <stddef.h>

static char	is_all_same_letter(char *str, char tested);
static char	handle_options(char **array, size_t *index);
int			ft_echo(char **array);

/**
 * @brief Echo with -n option
 * OPTIONS :
 *  -n : print without the triling newline
 *
 * NOTES : you can add any number of n after -n if you want
 *
 * @param array array of strings
 * @return int 0 OK, error otherwise
 */
int	ft_echo(char **array)
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
			printn_fd(1, " ", 1);
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
