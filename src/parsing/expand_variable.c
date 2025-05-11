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

char	**expand_variables_tokens(char **tokens);

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

// TODO need to replace ft_exit_int by ft_exit_int_np
static char	*create_str_with_params(t_params *params)
{
	char	*str;
	size_t	len;
	size_t	str_len;

	if (!params)
		return (NULL);
	str = malloc_gb(count_size_total_params(params) + 1);
	if (!str)
	{
		perror("minishell: malloc");
		ft_exit_int(1);
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
	if (head == NULL && str == NULL)
		str = ft_strdup_gb(NULL);
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
	size_t		i;
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
