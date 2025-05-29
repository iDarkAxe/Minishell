/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:35 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/08 14:20:59 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

static void	add_var_and_param(t_env_vars *env, char *var, char *content,
		char *array)
{
	t_var	*new;
	t_bool	equal;

	new = get_var(var);
	if (!new)
		ft_exit_int(-1);
	equal = FALSE;
	equal = detect_equal(array);
	if (content != NULL || (equal == TRUE && content == NULL))
		new->head_params = get_param(content, equal);
	else
		new->head_params = NULL;
	ft_varsadd_front(&env->head_var, new);
	return ;
}

static void	free_element(char **array)
{
	free(array[0]);
	free(array[1]);
	free(array);
}

static void	add_or_replace(t_env_vars *env, char **elements, char **array,
		size_t i)
{
	t_var	*temp;
	t_bool	equal;

	equal = detect_equal(array[i]);
	temp = search_env_var(env, elements[0]);
	if (temp == NULL || ft_strcmp(elements[0], temp->value) != 0)
		add_var_and_param(env, elements[0], elements[1], array[i]);
	else
		replace_param(temp, elements[1], equal);
	free_element(elements);
}

int	ft_export(char **array)
{
	size_t		i;
	char		**elements;
	t_env_vars	*env;
	int			check_errors;

	i = 0;
	env = get_env();
	if (!array || array[0] == NULL)
		sort_ascii_order(env);
	while (array[i])
	{
		check_errors = check_args_export(array[i]);
		if (check_errors == 2 || check_errors == 1)
			return (check_errors);
		elements = build_elements(array[i]);
		if (!elements)
			ft_exit_int(-1);
		add_or_replace(env, elements, array, i);
		i++;
	}
	return (0);
}
