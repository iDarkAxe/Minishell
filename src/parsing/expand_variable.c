/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:05:11 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/18 09:46:40 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "garbage.h"
#include "libft.h"
#include "parsing.h"

char	*search_env_str(const char *var, size_t size)
{
	char		*str;
	t_var		*head;
	t_env_vars	*env;

	env = get_env();
	head = env->head_var;
	str = NULL;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, var, size) == 0)
		{
			str = create_str_with_params(head->head_params);
			if (!str)
				return (NULL);
		}
		head = head->next;
	}
	if (head == NULL && str == NULL)
		str = ft_strdup(NULL);
	return (str);
}

char	*handle_expand(char *str)
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
		{
			i++;
			size = ft_strlen_charset(&str[i], "$\'\"");
			temp = search_env_str(&str[i], size);
			i += size;
		}
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
