/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_str_with_params.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:55:14 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 15:18:32 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"
#include "env.h"
#include <stdlib.h>

/**
 * @brief count_size_total_params count the total of params
 *
 * @param params params to count 
 * @return size_t 
 */
static size_t	count_size_total_params(t_params *params)
{
	size_t	count;

	count = 0;
	if (!params)
		return (0);
	while (params != NULL)
	{
		count += ft_strlen(params->value);
		if (params->next)
			count += 1;
		params = params->next;
	}
	return (count);
}

/**
 * @brief create_str_with_params transform params into a string 
 *
 * @param params params to transform into a string 
 * @return char *
 */
char	*create_str_with_params(t_garbage *garbage, t_params *params)
{
	char	*str;
	size_t	len;
	size_t	str_len;

	if (!params)
		return (NULL);
	str = malloc((count_size_total_params(params) + 1) * sizeof(char));
	if (str == NULL)
	{
		ft_dprintf(2,
			"minishell: malloc: Critical error of malloc, exiting.\n");
		ft_exit_int_np(garbage, EXIT_FAILURE);
	}
	str_len = 0;
	while (params != NULL)
	{
		len = ft_strlen(params->value);
		ft_memcpy(&str[str_len], params->value, len);
		str_len += len;
		if (params->next)
			str[str_len++] = ':';
		params = params->next;
	}
	str[str_len] = '\0';
	return (str);
}
