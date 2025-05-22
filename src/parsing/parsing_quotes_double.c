/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes_double.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:53:35 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/22 17:20:31 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include <stdio.h>

// char	*ft_remove_near_quotes(char const *str, const char character);
// char	*ft_remove_all_near_quotes(const char *str, const char character);

/**
 * @brief Remove the first iteration of found pair of character
 * and returns the new string
 *
 * @param str string to remove pair from
 * @param character character to delete
 * @return char* new string that don't contain the pair,
 * NULL if no pair to remove
 */
/* char	*ft_remove_near_quotes(const char *str, const char character)
{
	char	*start;
	size_t	len;
	size_t	count_q;
	char	*temp;
	char	*new_temp;

	start = ft_strdup_gb(garbage, str);
	if (start == NULL)
		return (NULL);
	count_q = 1;
	len = 0;
	while (start != NULL)
	{
		if (start[len] == '\0')
			return (NULL);
		if (start[len] == character)
			count_q++;
		if (count_q % 2 == 0 && start[len] == character && start[len
				+ 1] == character)
			break ;
		len += 1;
	}
	ft_strlcpy(&start[len], &str[len + 2], ft_strlen(start) - len - 1);
	return (start);
} */
/**
 * @brief Remove the all iteration of found pairs of character
 * and returns the new string
 *
 * @param str string to remove pair from
 * @param character character to delete
 * @return char* new string that don't contain the pair,
 * NULL if ERROR OR no pair found
 */
/* char	*ft_remove_all_near_quotes(t_garbage *garbage, const char *str,
		const char character)
{
	if (str == NULL || str[0] == '\0')
		return (NULL);
	temp = ft_strdup_gb(garbage, str);
	if (temp == NULL)
		return (NULL);
	while (1)
	{
		new_temp = ft_remove_near_quotes(temp, character);
		if (new_temp == NULL)
			return (temp);
		if (ft_strlen(new_temp) == ft_strlen(temp))
			break ;
		free_element_gb(garbage, temp);
		temp = new_temp;
	}
	return (temp);
}
 */