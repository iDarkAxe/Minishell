/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:05:11 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/02 13:59:40 by lud-adam         ###   ########.fr       */
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

static char	*expand_variables(t_data *data, char **str, size_t *size)
{
	char	*temp;

	*str += 1;
	*size = ft_strlen_charset((*str), "$\'\" ");
	if (*size == 0)
		return (NULL);
	if (**str == '?')
		temp = ft_itoa(data->ret);
	else
		temp = search_env_str(&data->garbage, &data->env, (*str), *size);
	if (!temp)
		return (NULL);
	(*str) += *size;
	return (temp);
}

static char	*fill_temp(t_data *data, char **str)
{
	char	*temp;
	size_t	size;

	temp = NULL;
	if (**str == '$' && (ft_isspace(*(*str + 1)) == *(*str + 1) || *(*str
				+ 1) == '\0') && *(*str + 1) != '"')
	{
		temp = ft_strdup("$");
		*str += 1;
	}
	else if (**str == '$' && (*(*str + 1) == '"' || *(*str + 1) == '\''))
	{
		size = ft_strlen_charset(*str + 2, "\"\'");
		temp = ft_strndup((*str) + 2, size);
		*str += (size + 3);
	}
	else if (**str == '$')
		temp = expand_variables(data, str, &size);
	else
	{
		size = ft_strlen_charset(*str, "$");
		temp = ft_strndup(*str, size);
		*str += size;
	}
	return (temp);
}

char	*handle_expand(t_data *data, char *str)
{
	char	*result;
	char	*temp;

	result = NULL;
	temp = NULL;
	while (*str)
	{
		temp = fill_temp(data, &str);
		if (!temp)
			return (NULL);
		result = fill_string(result, temp);
		free(temp);
		if (!result)
			return (NULL);
	}
	return (result);
}
