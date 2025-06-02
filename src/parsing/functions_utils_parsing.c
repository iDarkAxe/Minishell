/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:43:45 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/27 15:33:54 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "garbage.h"

#include <stdlib.h>

t_bool	is_dollar(char *str);
t_bool	detect_quote(const char *str);
char	*fill_string(t_garbage *garbage, char *result, char *temp);

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

char	*fill_string(t_garbage *garbage, char *result, char *temp)
{
	char	*temp_result;

	temp_result = NULL;
	if (!result)
	{
		result = ft_strdup(temp);
		if (!result)
			return (NULL);
	}
	else if (result && temp)
	{
		temp_result = ft_strdup(result);
		if (!temp_result)
			return (NULL);
		free(result);
		result = ft_strjoin(temp_result, temp);
		if (!result)
			return (NULL);
		free(temp_result);
	}
	free_element_gb(garbage, temp);
	return (result);
}
