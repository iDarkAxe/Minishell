/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:30:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/17 19:08:50 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Create a copy of source into a new pointer
 *	NEEDS to be freed

 * @param source string to copy
 * @return char* pointer to the new string
 */
char	*ft_strdup(const char *source)
{
	char	*pointer;
	size_t	count;
	size_t	index;

	count = ft_strlen(source);
	pointer = malloc(sizeof(char) * (count + 1));
	if (pointer == NULL)
		return (NULL);
	index = 0;
	while (count > 0)
	{
		pointer[index] = source[index];
		index++;
		count--;
	}
	pointer[index] = '\0';
	return (pointer);
}

/**
 * @brief Create a copy of source into a new pointer of size len
 *	NEEDS to be freed

 * @param source string to copy
 * @param len size of the new string
 * @return char* pointer to the new string
 */
char	*ft_strndup(const char *source, size_t len)
{
	char	*pointer;
	size_t	index;

	pointer = malloc(sizeof(char) * (len + 1));
	if (pointer == NULL)
		return (NULL);
	index = 0;
	while (index < len)
	{
		pointer[index] = source[index];
		index++;
	}
	pointer[len] = '\0';
	return (pointer);
}
