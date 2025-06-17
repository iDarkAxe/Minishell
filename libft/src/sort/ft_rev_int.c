/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:40:44 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 12:26:58 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_rev_int(int *tab, size_t size);

/**
 * @brief Reverse an array of ints
 *
 * @param tab adress of the first element of the array
 * @param size number of elements in the array
 */
void	ft_rev_int(int *tab, size_t size)
{
	int		temp;
	size_t	index;

	index = 0;
	while (index < (size / 2))
	{
		temp = tab[index];
		tab[index] = tab[size - index - 1];
		tab[size - index - 1] = temp;
		index++;
	}
}
