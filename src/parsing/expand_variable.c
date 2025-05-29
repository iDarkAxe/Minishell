/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:05:11 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/27 15:34:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "garbage.h"
#include "libft.h"
#include "parsing.h"

char	*search_env_str(t_garbage *garbage, t_env_vars *env, const char *var,
	size_t size)
{
	char	*str;
	t_var	*head;

	head = env->head_var;
	str = NULL;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, var, size) == 0)
		{
			str = create_str_with_params(garbage, head->head_params);
			if (!str)
				return (NULL);
		}
		head = head->next;
	}
	if (head == NULL && str == NULL)
		str = ft_strdup(NULL);
	return (str);
}

static char	*expand_variables(t_data *data, char *str, size_t *size, size_t *i)
{
	char	*temp;

	(*i)++;
	*size = ft_strlen_charset(&str[*i], "$\'\" ");
	temp = search_env_str(&data->garbage, &data->env, &str[*i], *size);
	if (!temp)
		return (NULL);
	(*i) += *size;
	return (temp);
}

char	*handle_expand(t_data *data, char *str)
{
	size_t	i;
	size_t	size;
	char	*result;
	char	*temp;

	result = NULL;
	temp = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			temp = expand_variables(data, str, &size, &i);
		else
		{
			size = ft_strlen_charset(&str[i], "$");
			temp = ft_strndup(&str[i], size);
			if (!temp)
				return (NULL);
			i += size;
		}
		result = fill_string(result, temp);
	}
	return (result);
}
