/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:43:45 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/03 14:35:39 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include <stdlib.h>

t_bool	is_dollar(char *str);
t_bool	detect_quote(const char *str);
char	*fill_string(char *result, char *temp);

t_bool	is_dollar(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	detect_quote(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*fill_string(char *result, char *temp)
{
	char	*temp_result;

	temp_result = NULL;
	if (temp == NULL)
		return (NULL);
	if (!result)
	{
		result = ft_strdup(temp);
		if (!result)
			return (NULL);
	}
	else if (result)
	{
		temp_result = ft_strdup(result);
		free(result);
		if (!temp_result)
			return (NULL);
		result = ft_strjoin(temp_result, temp);
		free(temp_result);
		if (!result)
			return (NULL);
	}
	return (result);
}
