/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:50:23 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/18 16:19:35 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "builtins.h"
#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static t_var	*fill_var(t_garbage *garbage, char *envp[], size_t *i);

/**
 * @brief get_var_value fill the string of a t_var
 * @param garbage garbage structure
 * @param str string
 * @param i reference of index to keep the track inside str 
 * @return t_params or NULL if fail 
 */
static char	*get_var_value(t_garbage *garbage, const char *str, size_t *i)
{
	char	*var;
	size_t	size;

	if (!str)
		return (NULL);
	size = ft_strlen_choose_c(str, '=');
	var = malloc_gb(garbage, sizeof(char) * (size + 1));
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

/**
 * @brief get_sub_params fill params with the content of str 
 * @param str string to copy, 
 * @param i reference of index to keep the track inside str 
 * @return t_params or NULL if fail 
 */
static t_params	*get_sub_params(t_garbage *garbage, const char *str, size_t *i)
{
	t_params	*params;
	size_t		j;

	j = 0;
	if (!str)
		return (NULL);
	params = malloc_gb(garbage, sizeof(t_params));
	if (!params)
		return (NULL);
	params->value = malloc_gb(garbage, sizeof(char)
			* (ft_strlen_choose_c(&str[*i], ':') + 1));
	if (!params->value)
	{
		free_element_gb(garbage, params);
		return (NULL);
	}
	while (str[*i] && (str[*i] != ':'))
	{
		params->value[j] = str[*i];
		(*i)++;
		j++;
	}
	params->value[j] = '\0';
	params->next = NULL;
	return (params);
}

/**
 * @brief get_params fill params of a t_var
 * @param str string to copy, 
 * @param i reference of index to keep the track inside str 
 * @return t_params or NULL if fail 
 */
static t_params	*get_params(t_garbage *garbage, const char *str, size_t *i)
{
	t_params	*params;
	t_params	*new_param;

	new_param = NULL;
	params = NULL;
	while (str[*i])
	{
		new_param = get_sub_params(garbage, str, i);
		if (!new_param)
			return (NULL);
		new_param->next = NULL;
		ft_paramsadd_back(&params, new_param);
		if (str[*i] == ':')
			(*i)++;
	}
	if (str[*i - 1] == ':' && str[*i] == '\0')
	{
		new_param = get_sub_params(garbage, str, i);
		if (!new_param)
			return (NULL);
		ft_paramsadd_back(&params, new_param);
	}
	return (params);
}

/**
 * @brief fill_var fill the name of environment variable and content of this one 
 * @param envp shell environment of the user, 
 * @param i reference of the index to keep a track inside envp
 * @return t_var 
 */
static t_var	*fill_var(t_garbage *garbage, char *envp[], size_t *i)
{
	size_t	j;
	t_var	*new;

	j = 0;
	new = malloc_gb(garbage, sizeof(t_var));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->value = get_var_value(garbage, envp[*i], &j);
	if (!new->value)
	{
		free_element_gb(garbage, new);
		return (NULL);
	}
	j++;
	new->head_params = get_params(garbage, envp[*i], &j);
	if (!new->head_params)
		return (new);
	return (new);
}

/**
 * @brief set_env allow to set the shell environment
 * @param envp shell environment of the user
 */
void	set_env(t_data *data, char *envp[])
{
	t_var	*new;
	size_t	i;

	data->env.head_var = NULL;
	data->last_token = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new = fill_var(&data->garbage, envp, &i);
		if (!new)
		{
			perror("minishell");
			free_garbage(&data->garbage);
			exit(EXIT_FAILURE);
		}
		ft_varsadd_back(&(data->env.head_var), new);
		i++;
	}
	update_shlvl(&data->garbage, &data->env);
	create_last_tokens_var(&data->garbage, &data->env);
	change_cwd(data, 1);
	ft_export(data, (char *[]){"OLDPWD", NULL});
}
