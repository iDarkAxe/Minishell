/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:53:17 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/29 10:38:03 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "libft.h"

static size_t	count_size_total_params(t_params *params)
{
	size_t	count;

	count = 0;
	if (!params)
		return (0);
	while (params != NULL)
	{
		count += ft_strlen(params->value) + 1;
		params = params->next;
	}
	return (count);
}

static char	*create_str_with_params(t_params *params)
{
	char	*str;
	size_t	i;
	size_t	size;

	i = 0;
	if (!params)
		return (NULL);
	str = malloc_gb(count_size_total_params(params));
	if (!str)
		return (NULL);
	while (params != NULL)
	{
		size = ft_strlen(params->value);
		ft_memcpy(&str[i], params->value, size);
		i += size;
		if (params->next)
			str[i++] = ':';
		params = params->next;
	}
	str[i] = '\0';
	return (str);
}

char	*search_env(t_env_vars *env, char *var)
{
	char	*str;
	t_var	*head;

	head = env->head_var;
	str = NULL;
	while (head != NULL)
	{
		if (ft_strcmp(head->value, var) == 0)
		{
			str = create_str_with_params(head->head_params);
			if (!str)
				return (NULL);
		}
		head = head->next;
	}
	return (str);
}
