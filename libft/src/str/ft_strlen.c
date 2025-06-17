/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/13 23:46:41 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *the_string);
size_t	ft_strlen_char(const char *the_string, int character);

/**
 * @brief Len of string without '\0'
 *
 * @param the_string string to check
 * @return size_t len of the string
 */
size_t	ft_strlen(const char *the_string)
{
	size_t	count;

	if (the_string == NULL)
		return (0);
	count = 0;
	while (the_string[count] != '\0')
		count++;
	return (count);
}

/**
 * @brief Number of occurrence of character in the string
 *
 * @param the_string string to check
 * @param character character to count
 * @return size_t len of the string
 */
size_t	ft_strlen_char(const char *the_string, int character)
{
	size_t	count;
	size_t	index;

	if (the_string == NULL)
		return (0);
	index = 0;
	count = 0;
	while (the_string[index] != '\0')
	{
		if (the_string[index] == (char)character)
			count++;
		index++;
	}
	return (count);
}
