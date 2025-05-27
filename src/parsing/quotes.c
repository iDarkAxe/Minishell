/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:43:27 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/26 18:35:35 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>

static void	handle_quote(const char *str, t_bool *expand, size_t *i, char *q)
{
	if (*q == str[*i])
	{
		*q = 0;
		*expand = TRUE;
		(*i)++;
	}
	else if (*q == 0 && (str[*i] == '\'' || str[*i] == '"'))
	{
		*q = str[*i];
		(*i)++;
	}
	if (*q == '\'')
		*expand = FALSE;
	else if (*q == '"')
		*expand = TRUE;
}

static void	fill_res(const char *s, char **res, size_t size, t_bool *expand)
{
	char	*temp;
	char	*temp_1;

	temp = ft_strndup(s, size);
	if (!temp)
		return ;
	if (*expand == TRUE)
	{
		temp_1 = handle_expand(temp);
		if (!temp_1)
			return ;
		*res = fill_string(*res, temp_1);
	}
	else
		*res = fill_string(*res, temp);
}

static size_t	compute_size(const char *str, char quote)
{
	size_t	size;

	size = 0;
	if (quote == 0 || ((detect_quote(str) == TRUE) && quote == 0))
		size = ft_strlen_charset(str, "\"\'");
	else
		size = ft_strlen_choose_c(str, quote);
	return (size);
}

static char	*remove_quote(const char *str, t_bool *expand)
{
	char	*result;
	char	quote;
	size_t	i;
	size_t	size;

	result = NULL;
	i = 0;
	quote = 0;
	while (str && str[i])
	{
		handle_quote(str, expand, &i, &quote);
		if (str[i] == '\0')
			break ;
		size = compute_size(&str[i], quote);
		if (size != 0)
			fill_res(&str[i], &result, size, expand);
		else
		{
			handle_quote(str, expand, &i, &quote);
			if (str[i] == '\0')
				break ;
		}
		i += size;
	}
	return (result);
}

static void	handle_quote_for_check(const char *str, t_bool *expand, size_t *i, char *q)
{
	if (*q == str[*i])
	{
		*q = 0;
		*expand = TRUE;
		(*i)++;
	}
	else if (*q == 0 && (str[*i] == '\'' || str[*i] == '"'))
	{
		*q = str[*i];
		(*i)++;
	}
	if (*q == '\'')
		*expand = FALSE;
	else if (*q == '"')
		*expand = TRUE;
}

t_bool	check_quote(const char *str)
{
	size_t	i;
	char	*quote;
	size_t	count_quote;

	i = 0;
	quote = 0;
	while (str && str[i])
	{
		if (q == str[i])
		{
			q = 0;
			i++;
		}
		else if (q == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			q = str[i];
			i++;
		}
		if (quote == '"')
			count_quote++;
		i++;
	}
	return (count_quote);
}

char	*setup_string(const char *str)
{
	t_bool	expand;
	char	*result;
	char	*str_expanded;

	expand = TRUE;
	result = NULL;
	str_expanded = remove_quote(str, &expand);
	if (!str_expanded)
		return (NULL);
	return (str_expanded);
}
