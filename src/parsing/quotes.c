/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:43:27 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/03 16:50:26 by ppontet          ###   ########lyon.fr   */
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

static size_t	compute_size(const char *str, char quote)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	if ((quote == 0 || ((detect_quote(str) == TRUE) && quote == 0))
		&& str[0] != '$')
		size = ft_strlen_charset(str, "$\"\'");
	else if (str[0] == '$' && (str[1] == '"' || str[1] == '\''))
		size = ft_strlen_charset(str, " \0");
	else if ((quote == 0 || ((detect_quote(str) == TRUE) && quote == 0)))
		size = ft_strlen_charset(str, "\"\'");
	else
		size = ft_strlen_choose_c(str, quote);
	return (size);
}

static void	fill_res(t_data *data, const char *s, char **res, char quote)
{
	char	*temp;
	char	*temp_1;
	size_t	size;

	size = compute_size(s, quote);
	temp = ft_strndup(s, size);
	if (!temp)
		return ;
	if ((quote == '"' || quote == 0))
	{
		temp_1 = handle_expand(data, temp);
		if (!temp_1)
			return ;
		*res = fill_string(*res, temp_1);
		free(temp_1);
	}
	else
	{
		*res = fill_string(*res, temp);
	}
	free(temp);
}

static char	*remove_quote(t_data *data, const char *str, char *quote)
{
	char	*result;
	size_t	i;
	size_t	size;

	result = NULL;
	i = 0;
	while (str && str[i])
	{
		handle_quote(str, &i, quote);
		if (str[i] == '\0')
			break ;
		size = compute_size(&str[i], *quote);
		if (size != 0)
			fill_res(data, &str[i], &result, *quote);
		else
		{
			handle_quote(str, &i, quote);
			if (str[i] == '\0')
				break ;
		}
		i += size;
	}
	return (result);
}

char	*setup_string(t_data *data, char *str)
{
	char	*str_expanded;
	char	quote;

	quote = 0;
	str_expanded = remove_quote(data, str, &quote);
	if (!str_expanded)
		return (NULL);
	if (quote != 0)
	{
		ft_dprintf(2, "minishell: syntax error: Unclosed quote: `%c'\n", quote);
		data->command->return_value = 2;
		data->command->parse_error = 1;
		return (NULL);
	}
	add_to_garbage(&data->garbage, str_expanded);
	return (str_expanded);
}
