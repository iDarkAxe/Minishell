/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:35 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/23 12:08:23 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

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
	ft_varsadd_front(&data->env.head_var, new);
	return ;
}

static void	free_element(char **array)
{
	free(array[0]);
	free(array[1]);
	free(array);
}

static void	add_or_replace(t_data *data, char **elements, char **array,
		size_t i)
{
	t_var	*temp;
	t_bool	equal;

	equal = detect_equal(array[i]);
	temp = search_env_var(&data->env, elements[0]);
	if (ft_strcmp(elements[0], temp->value) != 0)
		add_var_and_param(data, elements[0], elements[1], array[i]);
	else
		replace_param(&data->garbage, temp, elements[1], equal);
	free_element(elements);
}

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
