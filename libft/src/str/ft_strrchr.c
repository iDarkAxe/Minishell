/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:05:54 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 13:15:45 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

const char	*ft_strrchr(const char *string, int searched_char);

/**
 * @brief Find last occurrence of searched_char
 *
 * @param string string to search in
 * @param searched_char character to search
 * @return char* pointer to the last occurrence of searched_char
 */
const char	*ft_strrchr(const char *string, int searched_char)
{
	unsigned long int	i;

	i = 0;
	while (string[i] != '\0')
		i++;
	while (i > 0)
	{
		if (string[i] == (char)searched_char)
			return (&string[i]);
		i--;
	}
	if (string[i] == (char)searched_char)
		return (&string[i]);
	return (NULL);
}
