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
#include <stddef.h>
#include <stdlib.h>

char	*strndup_without_characters(const char *str, size_t size,
		char character)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(size * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == character)
			i++;
		new_str[j] = str[i];
		i++;
		j++;
	}
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
		if (is_separators(str[i], "\"\'"))
			count++;
		i++;
	}
	size = ft_strlen(str) - count + 1;
	new_str = strndup_without_characters(str, size, quote);
	if (!new_str)
		return (NULL);
	return (new_str);
}

#include <stdio.h>
int	main(void)
{
	char	str[] = "\"in\"f\"ile\" \"cat\" \"blabla\"";
	char	*new_str;

	new_str = remove_quote(str, '\"');
	printf("%s\n", new_str);
	free(new_str);
	return (0);
}
