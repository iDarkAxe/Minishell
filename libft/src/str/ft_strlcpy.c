/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:58:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 13:16:00 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, char *src, size_t size);

/**
 * @brief Copy of src into dst, up to size bytes
 *
 * @param dst destination string
 * @param src source string
 * @param size size of the destination string
 * @return size_t size of src
 */
size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	index;
	size_t	src_len;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	index = 0;
	while ((src[index] != '\0') && (index < (size - 1)))
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (src_len);
}
