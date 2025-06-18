/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:35 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 15:02:13 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"
#include "env.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

/**
 * @brief replace_param replace params of a t_param
 * @param var t_var to replace the params, new_content new content 
 * to put inside param 
 */
static void	replace_param(t_garbage *garbage, t_var *var, char *new_content,
		size_t equal)
{
	char	*new_value;

	if (!var || (var && !new_content && equal == FALSE))
		return ;
	new_value = ft_strdup_gb(garbage, new_content);
	var->head_params = get_param(garbage, new_content, equal);
	if (var->head_params == NULL && equal == TRUE)
	{
		var->head_params->value = new_value;
		return ;
	}
	if (var->head_params != NULL)
	{
		free_element_gb(garbage, var->head_params->value);
		var->head_params->value = new_value;
	}
}

/**
 * @brief Add_var_and_param take the name key and value and create a var 
 * and param associate to the var and add this inside env
 * @param var string that the name of the t_var
 * @param content string to transform in param and add this one to t_var 
 */
static void	add_var_and_param(t_data *data, char *var, char *content,
		char *array)
{
	t_var	*new;
	t_bool	equal;

	new = get_var(&data->garbage, var);
	if (!new)
		ft_exit_int(&data->garbage, -1);
	equal = detect_equal(array);
	if (content != NULL || (equal == TRUE && content == NULL))
		new->head_params = get_param(&data->garbage, content, equal);
	else
		new->head_params = NULL;
	ft_varsadd_back(&data->env.head_var, new);
	return ;
}

/**
 * @brief Free_element free a double array
 * @param array array of string that contains the var and the value to free 
 */
static void	free_element(char **array)
{
	free(array[0]);
	free(array[1]);
	free(array);
}

/**
 * @brief Add_or_replace add var if not exist or replace this one
 * @param elements array of string that contains the var/value to add or replace 
 */
static void	add_or_replace(t_data *data, char **elements, char **array,
		size_t i)
{
	t_var	*temp;
	t_bool	equal;

	equal = detect_equal(array[i]);
	temp = search_env_var(&data->env, elements[0]);
	if (temp == NULL)
		temp = data->env.head_var;
	if (temp && ft_strcmp(elements[0], temp->value) != 0)
		add_var_and_param(data, elements[0], elements[1], array[i]);
	else
		replace_param(&data->garbage, temp, elements[1], equal);
	free_element(elements);
}

/**
 * @brief ft_export allows to export environment variables inside env, 
 * if export without arg* uments display env sort in ascii order
 * @param array array of string with the key/value of the var to put inside env
 * @return int 0 if is ok
 */
int	ft_export(t_data *data, char **array)
{
	size_t		i;
	char		**elements;
	t_env_vars	*env;
	int			check_errors;

	i = 0;
	env = &data->env;
	if (!array || array[0] == NULL)
		sort_ascii_order(&data->garbage, env);
	while (array[i])
	{
		check_errors = check_args_export(array[i]);
		if (check_errors == 2 || check_errors == 1)
			return (check_errors);
		elements = build_elements(array[i]);
		if (elements == NULL)
		{
			ft_dprintf(2,
				"minishell: malloc: Critical error of malloc, exiting.\n");
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		}
		add_or_replace(data, elements, array, i);
		i++;
	}
	return (0);
}
