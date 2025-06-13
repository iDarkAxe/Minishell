/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:06:05 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 13:39:21 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	ft_strlen_var_trad(char *str);

size_t	ft_strlen_var_trad(char *str)
{
	size_t	size;

	size = 0;
	if (!str)
		return (0);
	if (*str == '$' && (str[1] == '\'' || str[1] == '"'))
	{
		size = 2;
		str += 2;
	}
	while (*str != '\0' && (*str != '\'' && *str != '"'))
	{
		size++;
		str++;
	}
	size++;
	return (size);
}

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
