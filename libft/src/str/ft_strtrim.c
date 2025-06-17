/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:59:56 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 12:33:23 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Deletes all characters that exist in s and set,
 * if they are at the beginning of the string or at the end
 *
 * @param s string to trim
 * @param set string of characters to trim
 * @return char* new string
 */
char	*ft_strtrim(char const *s, char const *set)
{
	char	*pointer;
	size_t	index;
	size_t	start;
	size_t	end;

	start = 0;
	index = 0;
	while (s[start] && ft_strchr(set, s[start]))
		start++;
	end = ft_strlen(s);
	while (end > start && ft_strchr(set, s[end - 1]))
		end--;
	pointer = malloc(sizeof(char) * (end - start + 1));
	if (pointer == NULL)
		return (NULL);
	while (start + index < end)
	{
		pointer[index] = s[start + index];
		index++;
	}
	pointer[index] = '\0';
	return (pointer);
}

// int	main(void)
// {
// 	char	*pointer;
// 	char	s1[] = "lorem \n ipsum \t dolor \n sit \t amet";

// 	// char	*string;
// 	// char	*set;
// 	// string = "xxxz  test with x and z and x .  zx  xx z\0";
// 	// set = "z x\0";
// 	pointer = ft_strtrim(s1, " ");
// 	printf("retour %s", pointer);
// }
