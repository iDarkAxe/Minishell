/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:43:34 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/17 19:09:10 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	pos_base(char str, char *base);
static int	is_in_base(char str, char *base);

/**
 * @brief Atoi with a particular base
 *
 * @param str String to convert
 * @param base Base to use for conversion
 * @return int converted number
 */
int	ft_atoi_base(char *str, char *base)
{
	int	sign;
	int	i;
	int	value;

	value = 0;
	i = 0;
	sign = 1;
	if (!ft_check_base_atoi(base))
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (is_in_base(str[i], base))
	{
		value *= (int)ft_strlen(base);
		value += pos_base(str[i], base);
		i++;
	}
	return (value * sign);
}

/**
 * @brief Search a character in base
 *
 * @param character character to search
 * @param base base to search in
 * @return int position of the character in the base
 */
static int	pos_base(char character, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0' && base[i] != character)
		i++;
	return (i);
}

/**
 * @brief Check if the base is valid
 *
 * @param str string to check
 * @param base base to check
 * @return int 1 if valid, 0 if not
 */
static int	is_in_base(char str, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (str == base[i])
			return (1);
		i++;
	}
	return (0);
}
