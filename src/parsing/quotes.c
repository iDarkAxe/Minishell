/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:43:27 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/11 14:37:21 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen_ignore_first_c(const char *str, char c)
{
	size_t	count_c;
	size_t	size;

	count_c = 0;
	size = 0;
	while (str && *str)
	{
		if (*str == c)
			count_c++;
		if (count_c == 2)
			return (size);
		str++;
		size++;
	}
	return (size);
}

static size_t	compute_size_quotes(const char *str, char quote)
{
	size_t	size;

	size = 0;
	if (quote == 0)
		size = ft_strlen_charset(str, "\'\"");
	else if (quote != 0)
		size = ft_strlen_choose_c(str, quote);
	return (size);
}

static void	handle_quote(const char *str, size_t *i, char *q)
{
	if (*q == str[*i])
	{
		*q = 0;
		(*i)++;
	}
	else if (*q == 0 && (str[*i] == '\'' || str[*i] == '"'))
	{
		*q = str[*i];
		(*i)++;
	}
}

char	*remove_quote(t_data *data, char *str, char *quote)
{
	char	*temp;
	char	*result;
	size_t	i;
	size_t	size;

	temp = NULL;
	i = 0;
	result = NULL;
	while (str && str[i])
	{
		handle_quote(str, &i, quote);
		if (str[i] == '\0')
			break ;
		size = compute_size_quotes(&str[i], *quote);
		if (size != 0)
		{
			temp = ft_strndup(&str[i], size);
			if (!temp)
			{
				ft_dprintf(2,
					"minishell: malloc: Critical error of malloc, exiting.\n");
				ft_exit_int_np(&data->garbage, EXIT_FAILURE);
			}
			result = fill_string(result, temp);
			free(temp);
		}
		handle_quote(str, &i, quote);
		if (str[i] == '\0')
			break ;
		i += size;
	}
	return (result);
}

char	*setup_string(t_data *data, char *str)
{
	char	*str_expanded;
	char	*result;
	char	quote;

	result = NULL;
	quote = 0;
	str_expanded = expand_str(data, str);
	if (!str_expanded)
		return (NULL);
	if (detect_quote(str_expanded) == FALSE)
		return (str_expanded);
	result = remove_quote(data, str_expanded, &quote);
	// if (quote != 0)
	// {
	// 	ft_dprintf(2, "minishell: syntax error: Unclosed quote: `%c'\n", quote);
	// 	// WARNING CAUSE SEGFAULT BECAUSE DATA COMMAND NO UNINITIALIZED
	// 	// data->command->return_value = 2;
	// 	// data->command->parse_error = 1;
	// 	return (NULL);
	// }
	free(str_expanded);
	return (result);
}
