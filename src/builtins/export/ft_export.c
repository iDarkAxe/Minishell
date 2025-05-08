/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:35 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/08 11:15:10 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

static void	add_var_and_param(t_env_vars *env, char *var, char *content,
		char *array)
{
	t_var	*new;
	size_t	detect_equal;
	size_t	i;

	new = get_var(var);
	if (!new)
		ft_exit_int(-1);
	detect_equal = 0;
	i = 0;
	while (array[i])
	{
		if (array[i] == '=')
		{
			detect_equal = 1;
			break ;
		}
		i++;
	}
	if (content != NULL || (detect_equal == 1 && content == NULL))
		new->head_params = get_param(content, detect_equal);
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
	if (ft_strcmp(elements[0], search_env_var(env, elements[0])->value) != 0)
		add_var_and_param(env, elements[0], elements[1], array[i]);
	else
		replace_param(search_env_var(env, elements[0]), elements[1]);
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
		elements = ft_split(array[i], '=');
		if (!elements)
			ft_exit_int(-1);
		add_or_replace(env, elements, array, i);
		i++;
	}
	return (0);
}
