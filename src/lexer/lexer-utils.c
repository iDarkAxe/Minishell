/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:21 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/11 11:08:19 by ppontet          ###   ########lyon.fr   */
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
 * @param c
 * @return int
 */
int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*ft_substr_end(char const *src, unsigned int start, size_t end)
{
	int		len;
	char	*s;

	len = end - start;
	s = malloc_gb(len + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, &src[start], len);
	s[len] = '\0';
	return (s);
}
