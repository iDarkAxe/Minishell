/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:58:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/17 18:28:16 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Allocates a new string, and returns the result of
 * a concatenation of s1 and s2

 * @param s1 string 1
 * @param s2 string 2
 * @return char* new string
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*pointer;
	size_t	len;
	size_t	s1_len;
	size_t	index;

	index = 0;
	s1_len = ft_strlen(s1);
	len = s1_len + ft_strlen(s2);
	pointer = malloc(sizeof(char) * (len + 1));
	if (pointer == NULL)
		return (NULL);
	while (s1[index] != '\0')
	{
		pointer[index] = s1[index];
		index++;
	}
	index = 0;
	while (s2[index] != '\0' && index < len - s1_len)
	{
		pointer[index + s1_len] = s2[index];
		index++;
	}
	pointer[index + s1_len] = '\0';
	return (pointer);
}
