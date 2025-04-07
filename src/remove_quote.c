/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:23:36 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/07 13:21:08 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

t_bool	detect_pair_quote(const char *str, char quote)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(str);
	if (str[0] == quote && str[size - 1] == quote)
		return (TRUE);
	return (FALSE);
}

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

// si premier quote = premier charactere de la string et si dernier character de str = a la premier quote
// 	tel remove selon la pair de quote

char	*clean_string(const char *str)
{
	char	*new_str;

	new_str = NULL;
	if (!str)
		return (NULL);
	if (detect_pair_quote(str, '\"') == TRUE)
		new_str = remove_quote(str, '\"');
	else if (detect_pair_quote(str, '\'') == TRUE)
		new_str = remove_quote(str, '\'');
	return (new_str);
}

#include <stdio.h>
int	main(void)
{
	// const char	str[] = "\"in\"f\"ile\" \"cat\" \"blabla\"";
	// const char	*str = "\"je suis une vache \"awev\"  \'tes\'t";
	// const char	*str = "je suis une vache \"awev\"";
	// const char	*str = "je suis une vache \"awev\"  \'tes\'t";
	const char *str = "\'je suis une vache \"awev\"  \'tes't \'";
	char	*new_str;

	new_str = clean_string(str);
	printf("%s\n", new_str);
	free(new_str);
	return (0);
}
