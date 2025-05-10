/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:05:11 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/10 15:49:31 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "builtins.h"

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

static char	*expand_variable(char *str, t_env_vars *env)
{
	char	*result;

	if (str == NULL || !env)
		return (NULL);
	result = search_env_str(env, str + 1); 
	return (result);
}


char	**expand_variables_tokens(char **tokens)
{
	size_t	i;
	t_env_vars	*env;

	if (tokens == NULL || tokens[0] == NULL)
		return (NULL);
	i = 0;
	env = get_env();
	while (tokens[i] != NULL)
	{
		printf("%s\n", tokens[i]);
		if (ft_strchr(tokens[i], '$') != NULL)
			tokens[i] = expand_variable(tokens[i], env);
		if (tokens[i] == NULL)
		{
			free_array(tokens);
			ft_exit_int(1);
		}
		i++;
	}
	return (tokens);
}
