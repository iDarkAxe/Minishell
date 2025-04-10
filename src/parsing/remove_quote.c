/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:23:36 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/10 18:19:35 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

char	*strndup_without_characters(const char *str, size_t size,
		char character)
{
	char	*new_str;
	size_t		i;
	size_t		j;

	if (!str)
		return (NULL);
	new_str = malloc(size + 1 * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j < size)
	{
		if (str[i] != character)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*remove_quote(const char *str, const char quote)
{
	char	*new_str;
	size_t	count;
	size_t	i;
	size_t	size;

	count = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == quote)
			count++;
		i++;
	}
	size = ft_strlen(str) - count;
	new_str = strndup_without_characters(str, size, quote);
	if (!new_str)
		return (NULL);
	return (new_str);
}

char	*clean_string(const char *str)
{
	char	*new_str;
	char	*temp;
	t_bool	pair;

	new_str = NULL;
	temp = NULL;
	pair = FALSE;
	if (!str)
		return (NULL);
	if (detect_pair_quote(str, '\'', &pair) == TRUE && pair == FALSE)
	{
		ft_remove_all_near_quotes(str, '"');
		new_str = remove_quote(str, '\'');
		free(temp);
	}
	else if (detect_pair_quote(str, '\"', &pair) == TRUE && pair == FALSE)
	{
		ft_remove_all_near_quotes(str, '\'');
		new_str = remove_quote(str, '\"');
		return (new_str);
	}
	return (new_str);
}
