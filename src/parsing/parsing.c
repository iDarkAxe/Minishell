/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:49:27 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/11 15:44:21 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "pipex.h"
#include "parsing.h"
#include <stddef.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

size_t	count_without_quote(const char *str)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (str && str[i])
	{
		if (quote && str[i] == quote)
			quote = 0;
		else if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else
			count++;
		i++;
	}
	return (count);
}

static t_bool	has_unclosed_quote(const char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (str && str[i])
	{
		if (quote && str[i] == quote)
			quote = 0;
		else if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		i++;
	}
	return (quote != 0);
}

char	*parsing_minishell(const char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	count;
	char	quote;

	if (!str || has_unclosed_quote(str))
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	count = count_without_quote(str);
	new_str = malloc((count + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (str && str[i])
	{
		if (quote && str[i] == quote)
			quote = 0;
		else if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
