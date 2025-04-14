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
#include "parsing.h"
#include "pipex.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdlib.h>

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
		if (quote != 0 && str[i] == quote)
			quote = 0;
		else if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
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
		if (quote != 0 && str[i] == quote)
			quote = 0;
		else if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		i++;
	}
	if (quote == 0)
		return (FALSE);
	return (TRUE);
}

static char	*remove_quote(const char *str, char *new_str)
{
	char	quote;
	size_t	i;
	size_t	j;
	
	i = 0;
	j = 0;
	quote = 0;
	while (str && str[i])
	{
		if (quote != 0 && str[i] == quote)
			quote = 0;
		else if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*parsing_minishell(const char *str)
{
	char	*new_str;
	size_t	count;

	if (!str || has_unclosed_quote(str) == TRUE)
		return (NULL);
	count = count_without_quote(str);
	new_str = malloc((count + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	new_str = remove_quote(str, new_str);
	return (new_str);
}
