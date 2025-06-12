/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>        +  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:35 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/12 17:45:49 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

/**
 * @brief add_var_and_param take the name key and value and create a var and param associate to the var and add this inside env
 * @param var string that the name of the t_var, content string to transform in param and add this one to t_var 
 * @return
 */
static void	add_var_and_param(t_data *data, char *var, char *content,
		char *array)
{
	t_var	*new;
	t_bool	equal;

	new = get_var(&data->garbage, var);
	if (!new)
		ft_exit_int(&data->garbage, -1);
	equal = FALSE;
	equal = detect_equal(array);
	if (content != NULL || (equal == TRUE && content == NULL))
		new->head_params = get_param(&data->garbage, content, equal);
	else
		new->head_params = NULL;
	ft_varsadd_back(&data->env.head_var, new);
	return ;
}

/**
 * @brief free_element free a double array
 * @param elements array of string that contains the var and the value to free 
 * @return
 */
static void	free_element(char **array)
{
	free(array[0]);
	free(array[1]);
	free(array);
}

/**
 * @brief add_or_replace add var if not exist or replace this one
 * @param elements array of string that contains the var and the value to add or replace 
 * @return
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
 * @brief ft_export allows to export environment variables inside env, if export without arg* uments display env sort in ascii order
 * @param array array of string with the key and value of the var to put inside env
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
		if (!elements)
			ft_exit_int(&data->garbage, -1);
		add_or_replace(data, elements, array, i);
		i++;
	}
	return (0);
}
