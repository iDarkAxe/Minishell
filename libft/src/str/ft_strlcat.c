/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:59:13 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 12:28:50 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * @brief Concatenate src into dst, up to size bytes
 *
 * @param dst destination string
 * @param src source string
 * @param size size of the destination string
 * @return unsigned int size of the new string
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	src_len;
	size_t	dst_len;

	index = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (src_len + size);
	while (dst_len + index < size - 1 && src[index])
	{
		dst[index + dst_len] = src[index];
		index++;
	}
	dst[index + dst_len] = '\0';
	return (src_len + dst_len);
}
