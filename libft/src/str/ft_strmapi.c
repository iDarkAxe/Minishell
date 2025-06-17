/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:46:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/17 18:29:15 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Apply the function ’f’ to each character of the string ’s’,
 * passing its index as first argument and the character itself as second
 * argument.
 *
 * @param s string to iterate
 * @param f function to apply
 * @return char* new string
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*pointer;

	if (!(*s != 0 || f != 0))
		return (NULL);
	pointer = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (pointer == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		pointer[i] = (*f)(i, s[i]);
		i++;
	}
	pointer[i] = '\0';
	return (pointer);
}
