/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoins_va.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:56:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 13:18:09 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

static size_t	count_len_va(va_list list);
char			*ft_strjoins_va(char const *str, ...);

/**
 * @brief Allocates a new string, and returns the result of
 * a concatenation of str and all the arguments
 * last argument needs to be "\0", NULL or "".

 * @param str string 1
 * @param ... Variadic arguments
 * @return char* new string
 */
char	*ft_strjoins_va(char const *str, ...)
{
	va_list	arg_ptr;
	size_t	count;
	size_t	index;
	char	*new_str;
	char	*temp;

	va_start(arg_ptr, str);
	count = ft_strlen(str);
	new_str = malloc(sizeof(char) * (count_len_va(arg_ptr) + count + 1));
	index = 0;
	ft_memcpy(&new_str[index], str, count);
	index += count;
	while (1)
	{
		temp = va_arg(arg_ptr, char *);
		if (temp == NULL || temp[0] == '\0')
			break ;
		count = ft_strlen(temp);
		ft_memcpy(&new_str[index], temp, count);
		index += count;
	}
	new_str[index] = '\0';
	va_end(arg_ptr);
	return (new_str);
}

static size_t	count_len_va(va_list list)
{
	va_list	arg_count_ptr;
	char	*temp;
	size_t	count;

	va_copy(arg_count_ptr, list);
	count = 0;
	while (1)
	{
		temp = va_arg(arg_count_ptr, char *);
		if (temp == NULL || temp[0] == '\0')
			break ;
		count += ft_strlen(temp);
	}
	va_end(arg_count_ptr);
	return (count);
}
