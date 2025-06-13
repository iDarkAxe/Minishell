/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:18:52 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/11 13:26:00 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

size_t	ft_strlen_dollars(char *str)
{
	size_t	size;

	size = 0;
	if (!str)
		return (0);
	if (*str == '$')
	{
		size++;
		str++;
	}
	while (*str && *str != '$' && *str != '\'' && *str != '"'
		&& ft_isspace(*str) == 0 && ft_is_special_character(*str) == FALSE)
	{
		size++;
		str++;
	}
	return (size);
}

size_t	ft_strlen_quotes_expand(char *str, char quote)
{
	size_t	size;

	size = 0;
	if (!str)
		return (0);
	if (*str == quote)
	{
		size++;
		str++;
	}
	while (*str && *str != '\'' && *str != '"' && ft_isalnum(*str) == 1
		&& ft_isspace(*str) == 0)
	{
		size++;
		str++;
	}
	if (*str == quote)
	{
		size++;
		str++;
	}
	return (size);
}

size_t	ft_strlen_quotes(char *str)
{
	size_t	size;
	char	quote;

	size = 0;
	quote = 0;
	while (str && *str)
	{
		size++;
		if (quote == 0 && (*str == '\'' || *str == '"'))
			quote = *str;
		else if (quote == *str)
			return (size);
		str++;
	}
	return (size);
}

static t_bool	is_charset(const char *charset, char c)
{
	size_t	i;

	i = 0;
	while (charset && charset[i])
	{
		if (charset[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

size_t	ft_strlen_charset(const char *str, const char *charset)
{
	size_t	i;

	i = 0;
	while (str && str[i] && is_charset(charset, str[i]) == FALSE)
		i++;
	return (i);
}
