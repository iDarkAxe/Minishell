/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:21 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/15 13:09:22 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "garbage.h"
#include "libft.h"

int		is_operator_char(char c);
char	*ft_substr_end(char const *src, unsigned int start, size_t end);

/**
 * @brief Is |, < or >
 *
 * @param c character to check
 * @return int 1 if c is operator, 0 otherwise
 */
int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * @brief Allocate memory for a string and copy the content from src
 *
 * @param src source string
 * @param start start index to copy from
 * @param end end index to copy to
 * @return char* pointer to the new string
 */
char	*ft_substr_end(char const *src, unsigned int start, size_t end)
{
	size_t		len;
	char		*s;

	len = end - start;
	s = malloc_gb(len + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, &src[start], len);
	s[len] = '\0';
	return (s);
}
