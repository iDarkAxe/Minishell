/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:57:01 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 12:34:49 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Check if base is valid for atoi_base
 *
 * @param base base to check
 * @return int 1 if valid, 0 if not
 */
size_t	ft_check_base_atoi(const char *base)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(base) <= 1)
		return (0);
	while (base[i] != '\0')
	{
		j = 0;
		while (base[j] != '\0')
		{
			if ((base[j] == base[i] || base[j] == '+' || base[j] == '-'
					|| (base[j] >= 9 && base[j] <= 13) || base[j] == ' ')
				&& i != j)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/**
 * @brief Check if base is valid for putnbr_base
 *
 * @param base base to check
 * @return int 1 if valid, 0 if not
 */
size_t	ft_check_base_putnbr(const char *base)
{
	size_t	index;
	size_t	base_length;
	size_t	tested;

	base_length = ft_strlen(base);
	if (base[0] == '\0' || base_length <= 1)
		return (0);
	tested = 0;
	while (tested < base_length)
	{
		index = tested + 1;
		while (index < base_length)
		{
			if (base[tested] == base[index] || base[tested] == '+'
				|| base[tested] == '-' || base[index] == '-'
				|| base[index] == '+')
				return (0);
			index++;
		}
		tested++;
	}
	return (base_length);
}
