/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:18:52 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 14:24:37 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

/**
 * @brief ft_strlen_dollars compute the size of expandable variable 
 *
 * @param str string to check
 * @return size of str 
 * */
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

/**
 * @brief ft_strlen_quotes_expand compute the size of translatable 
 * variable and count quotes and stop on this 
 *
 * @param str string to check
 * @param quote quote to stop 
 * @return size of str 
 * */
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

/**
 * @brief ft_strlen_quotes compute the size of str and stop on quotes 
 *
 * @param str string to check
 * @return size of str 
 * */
size_t	ft_strlen_quotes(char *str)
{
	size_t	size;
	char	quote;

	size = 0;
	quote = 0;
	if (!str)
		return (0);
	while (*str)
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

/**
 * @brief is_charset detect if character is inside the charset 
 *
 * @param charset list of characters
 * @param c character to check 
 * @return t_bool TRUE or FALSE 
 * */
static t_bool	is_charset(const char *charset, char c)
{
	size_t	i;

	i = 0;
	if (!charset)
		return (FALSE);
	while (charset[i])
	{
		if (charset[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/**
 * @brief ft_strlen_charset compute the size of str and stop on 
 * character inside charset
 *
 * @param str to expand, size give the size of str
 * @param charset characters to stop
 * @return size of str 
 * */
size_t	ft_strlen_charset(const char *str, const char *charset)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && is_charset(charset, str[i]) == FALSE)
		i++;
	return (i);
}
