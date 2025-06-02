/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:43:27 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/30 10:24:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "parsing.h"
#include "minishell.h"
#include "builtins.h"
#include "ft_printf.h"

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

static void	fill_res(t_data *data, const char *s, char **res, size_t size,
	char quote)
{
	char	*temp;
	char	*temp_1;

	temp = ft_strndup_gb(&data->garbage, s, size);
	if (!temp)
		return ;
	if ((quote == '"' || quote == 0) && temp[0] == '$')
	{
		temp_1 = handle_expand(data, temp);
		free_element_gb(&data->garbage, temp);
		if (!temp_1)
			return ;
		*res = fill_string(&data->garbage, *res, temp_1);
	}
	else
		*res = fill_string(&data->garbage, *res, temp);
}

static size_t	compute_size(const char *str, char quote)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	if ((quote == 0 || ((detect_quote(str) == TRUE) && quote == 0)) && str[0] != '$')
		size = ft_strlen_charset(str, "$\"\'");
	else if (str[0] == '$' && (str[1] == '"' || str[1] == '\''))
		size = ft_strlen_charset(str, " \0");
	else if ((quote == 0 || ((detect_quote(str) == TRUE) && quote == 0)))
		size = ft_strlen_charset(str, "\"\'");
	else
		size = ft_strlen_choose_c(str, quote);
	return (size);
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
			fill_res(data, &str[i], &result, size, *quote);
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
	char	*result;
	char	*str_expanded;
	char	quote;

	quote = 0;
	result = NULL;
	str_expanded = remove_quote(data, str, &quote);
	free_element_gb(&data->garbage, str);
	if (!str_expanded)
		return (NULL);
	add_to_garbage(&data->garbage, str_expanded);
	if (quote != 0)
	{
		ft_dprintf(2, "minishell: syntax error: Unclosed quote: `%c'\n", quote);
		return (NULL);
	}
	return (str_expanded);
}
