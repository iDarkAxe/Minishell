/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:50:23 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/18 11:49:57 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char	*get_var(const char *str, size_t *i)
{
	char	*var;
	size_t	size;

	if (!str)
		return (NULL);
	size = ft_strlen_choose_c(str, '=');
	var = malloc_gb(sizeof(char) * (size + 1));
	if (!var)
		return (NULL);
	while (str[*i] && str[*i] != '=' && *i < size)
	{
		var[*i] = str[*i];
		(*i)++;
	}
	var[*i] = '\0';
	return (var);
}

static t_params	*get_sub_params(const char *str, size_t *i)
{
	t_params	*params;
	size_t		j;

	j = 0;
	if (!str)
		return (NULL);
	params = malloc_gb(sizeof(t_params));
	if (!params)
		return (NULL);
	params->value = malloc_gb(sizeof(char) * (ft_strlen_choose_c(&str[*i], ':')
				+ 1));
	if (!params->value)
	{
		free_element_gb(params);
		return (NULL);
	}
	while (str[*i] && (str[*i] != ':'))
	{
		params->value[j] = str[*i];
		(*i)++;
		j++;
	}
	params->value[j] = '\0';
	return (params);
}

static t_params	*get_params(const char *str, size_t *i)
{
	t_params	*params;
	t_params	*new_param;

	if (!str)
		return (NULL);
	new_param = NULL;
	params = NULL;
	while (str[*i])
	{
		new_param = get_sub_params(str, i);
		new_param->next = NULL;
		if (!new_param)
			return (NULL);
		ft_paramsadd_back(&params, new_param);
		if (str[*i] == ':')
			(*i)++;
	}
	if (str[*i - 1] == ':' && str[*i] == '\0')
	{
		new_param = get_sub_params(str, i);
		new_param->next = NULL;
		if (!new_param)
			return (NULL);
		ft_paramsadd_back(&params, new_param);

	}
	return (params);
}

t_var	*fill_var(char *envp[], size_t *i)
{
	size_t	j;
	t_var	*new;

	j = 0;
	new = malloc_gb(sizeof(t_var));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->value = get_var(envp[*i], &j);
	if (!new->value)
	{
		free_element_gb(new);
		return (NULL);
	}
	j++;
	new->head_params = get_params(envp[*i], &j);
	if (!new->head_params)
	{
		free_element_gb(new->value);
		free_element_gb(new);
	}
	return (new);
}

t_env_vars	*get_env(char *envp[])
{
	t_env_vars	*env;
	t_var		*new;
	size_t		i;

	env = malloc_gb(sizeof(t_env_vars));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		new = fill_var(envp, &i);
		if (!new)
			return (NULL);
		ft_varsadd_back(&env->head_var, new);
		i++;
	}
	return (env);
}
