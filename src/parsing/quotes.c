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

static void	handle_quote(char **str, char *q)
{
	if (*q == **str)
	{
		*q = 0;
		(*str)++;
	}
	else if (*q == 0 && (**str == '\'' || **str == '"'))
	{
		*q = **str;
		(*str)++;
	}
}

static void	create_temp_and_fill_result(t_data *data, char **result, char *str,
		size_t size)
{
	char	*temp;

	temp = ft_strndup(str, size);
	if (!temp)
	{
		ft_dprintf(2,
			"minishell: malloc: Critical error of malloc, exiting.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	*result = fill_string(*result, temp);
	free(temp);
}

char	*remove_quote(t_data *data, char *str, char *quote)
{
	char	*result;
	size_t	size;

	result = NULL;
	while (str && *str)
	{
		handle_quote(&str, quote);
		if (*str == '\0')
			break ;
		size = compute_size_quotes(str, *quote);
		if (size != 0)
			create_temp_and_fill_result(data, &result, str, size);
		handle_quote(&str, quote);
		if (*str == '\0')
			break ;
		str += size;
	}
	return (result);
}
