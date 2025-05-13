/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:05:11 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/11 13:53:45 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "builtins.h"
#include "libft.h"
#include "parsing.h"

char	*expand_variables_line(char *line);

char	*search_env_str(t_env_vars *env, char *var, size_t size)
{
	char	*str;
	t_var	*head;

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

char	*expand_variables_line(char *str)
{
	char		*string_to_stack;
	t_env_vars	*env;
	char		*temp;
	char		*expand;
	size_t		size;
	size_t		i;

	string_to_stack = NULL;
	temp = NULL;
	size = 0;
	expand = NULL;
	env = get_env();
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			size = ft_strlen_charset(&str[i], "$ ");
			expand = search_env_str(env, &str[i], size);
			if (!expand)
				return (NULL);
			if (string_to_stack == NULL)
			{
				string_to_stack = ft_strdup(expand);
				if (!string_to_stack)
					return (NULL);
				free(expand);
			}
			else
			{
				temp = ft_strdup(string_to_stack);
				if (!temp)
					return (NULL);
				free(string_to_stack);
				string_to_stack = ft_strjoin(temp, expand);
				if (!string_to_stack)
					return (NULL);
				free(expand);
				free(temp);
			}
		}
		else
		{
			size = ft_strlen_choose_c(&str[i], '$');
			expand = ft_strndup(&str[i], size);
			temp = ft_strdup(string_to_stack);
			free(string_to_stack);
			string_to_stack = ft_strjoin(temp, expand);
			free(expand);
			free(temp);
			i += size;
			continue ;
		}
		i++;
	}
	return (string_to_stack);
}
