/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:53:17 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/06 13:29:18 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"

static size_t	count_size_total_params(t_params *params)
{
	size_t	count;

	count = 0;
	if (!params)
		return (0);
	while (params != NULL)
	{
		count += ft_strlen(params->value);
		params = params->next;
	}
	return (count);
}

static char	*create_str_with_params(t_params *params)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!params)
		return (NULL);
	str = malloc_gb(count_size_total_params(params) + 1);
	if (!str)
		return (NULL);
	while (params != NULL)
	{
		j = 0;
		while (params->value && params->value[j])
		{
			str[i] = params->value[j];
			i++;
			j++;
		}
		params = params->next;
	}
	str[i] = '\0';
	return (str);
}

char	*search_env_str(t_env_vars *env, char *var)
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

t_var	*search_env_var(t_env_vars *env, char *var)
{
	t_var	*head;
	t_var	*temp;

	head = env->head_var;
	temp = head;
	while (head != NULL)
	{
		if (ft_strcmp(head->value, var) == 0)
		{
			temp = head;
			break ;
		}
		head = head->next;
	}
	return (temp);
}
