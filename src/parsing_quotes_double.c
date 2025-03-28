/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes_double.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:53:35 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/28 16:13:57 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include <stdio.h>

char	*ft_remove_near_quotes(char const *str, const char character);
char	*ft_remove_all_near_quotes(const char *str, const char character);

char	*ft_remove_near_quotes(const char *str, const char character)
{
	char	*temp;
	char	*start;
	size_t	count_len;
	size_t	count_q;

	start = ft_strdup_gb(str);
	if (start == NULL)
		return (NULL);
	temp = start;
	count_q = 1;
	while (temp != NULL && *temp != '\0')
	{
		temp = ft_strchr(temp, character);
		if (temp == NULL)
			return (NULL);
		count_q += 1;
		if (count_q % 2 == 0 && *(temp + 1) == character)
			break ;
		temp += 1;
	}
	count_len = (size_t)(temp - start);
	ft_memmove(&start[count_len], &str[count_len + 2], ft_strlen(start)
		- (size_t)count_len);
	start[ft_strlen(start)] = '\0';
	return (start);
}

char	*ft_remove_all_near_quotes(const char *str, const char character)
{
	char	*temp;
	char	*new_temp;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	temp = ft_strdup_gb(str);
	if (temp == NULL)
		return (NULL);
	while (1)
	{
		new_temp = ft_remove_near_quotes(temp, character);
		if (new_temp == NULL || ft_strlen(new_temp) == ft_strlen(temp))
			break ;
		free_element_gb(temp);
		temp = new_temp;
	}
	return (temp);
}
