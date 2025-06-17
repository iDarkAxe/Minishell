/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:03:57 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/17 18:30:58 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Create a copy of source into a new pointer, at start, of size len
 *	NEEDS to be freed

 * @param src string to copy
 * @param start start of the copy
 * @param len size of the copy
 * @return char* new string
 */
char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char	*pointer;
	size_t	index;

	index = 0;
	if (start >= ft_strlen(src))
		return (ft_strdup(""));
	if (ft_strlen(&src[start]) < len)
		len = ft_strlen(&src[start]);
	pointer = malloc(sizeof(char) * (len + 1));
	if (pointer == NULL)
		return (NULL);
	while (index < len && src[index + start] != '\0')
	{
		pointer[index] = src[index + start];
		index++;
	}
	pointer[index] = '\0';
	return (pointer);
}

// #include <stdio.h>
//
// int		main(void)
// {
// 	char	str[] = "lorem ipsum dolor sit amet";
// 	char	*strsub;

// 	if (!(strsub = ft_substr(str, 7, 10)))
// 			printf("NULL");
// 		else
// 			printf("%src", strsub);
// 		if (str == strsub)
// 			printf("\nA new string was not returned");
// }
