/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:06:05 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 14:44:42 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	ft_strlen_var_trad(char *str);

/**
 * @brief ft_strlen_var_trad compute the size for translatable variable
 *
 * @param str string to compute size 
 * @return size of str 
 * */
size_t	ft_strlen_var_trad(char *str)
{
	size_t	size;
	char	quote;

	size = 0;
	quote = '\0';
	if (!str)
		return (0);
	if (*str == '$' && (str[1] == '\'' || str[1] == '"'))
	{
		quote = str[1];
		size = 2;
		str += 2;
	}
	while (*str != '\0' && *str != quote)
	{
		size++;
		str++;
	}
	size++;
	return (size);
}

/**
 * @brief compute_size compute the size of str in differentes cases.
 *
 * @param str string to compute size 
 * @return size of str 
 * */
size_t	compute_size(char *str)
{
	size_t	size;

	size = 0;
	if (*str == '$' && *(str + 1) == '?')
		size = 2;
	else if (*str == '$' && (*(str + 1) == '\'' || *(str + 1) == '"'))
		size = ft_strlen_var_trad(str);
	else if (*str == '$')
		size = ft_strlen_dollars(str);
	else if (*str == '\'' || *str == '"')
		size = ft_strlen_quotes(str);
	else if (ft_isalnum(*str) == 1 || ft_is_special_character(*str) == TRUE)
		size = ft_strlen_charset(str, "\'\"$");
	return (size);
}

/**
 * @brief compute_size_expand_var compute the size of expandable 
 * variable in differentes cases.
 *
 * @param str string to compute size 
 * @return size of str 
 * */
size_t	compute_size_expand_var(char *str)
{
	size_t	size;

	size = 0;
	if (ft_isalnum(*str) == 1 || *str == '/')
		size = ft_strlen_charset(str, "\'\"$=");
	if (*str == '$' && *(str + 1) == '?')
		size = 2;
	else if (*str == '$' && (*(str + 1) == '\'' || *(str + 1) == '"'))
		size = ft_strlen_var_trad(str);
	else if (*str == '"' || *str == '\'')
		size = ft_strlen_quotes_expand(str, *str);
	else if (*str == '$')
		size = ft_strlen_dollars(str);
	else if (ft_isspace(*str) != 0)
		size = ft_strlen_charset(str, "\"\'$");
	return (size);
}
