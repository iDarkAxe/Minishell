/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:35 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/02 17:40:25 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

static t_var	*get_var(const char *var)
{
	t_var	*new;

	new = malloc_gb(sizeof(t_var));
	if (!new)
		ft_exit_int(-1);
	new->next = NULL;
	new->value = ft_strdup_gb(var);
	if (!new->value)
		ft_exit_int(-1);
	return (new);
}

static t_params	*get_param(char *content)
{
	t_params	*param;

	param = malloc_gb(sizeof(t_params));
	if (!param)
		return (NULL);
	param->value = ft_strdup_gb(content);
	if (!param->value)
		return (NULL);
	return (param);
}

void	add_var_and_param(t_env_vars *env, char *var, char *content)
{
	t_var	*new;
	t_var	**head;

	new = get_var(var);
	if (!new)
		ft_exit_int(-1);
	new->head_params = get_param(content);
	if (!new->head_params)
		ft_exit_int(-1);
	head = &env->head_var;
	ft_varsadd_front(head, new);
	return ;
}

int	ft_export(char **array, t_env_vars *env)
{
	size_t		i;
	char		**elements;
	t_env_vars	*c_env;

	i = 1;
	elements = NULL;
	if (!env || !array)
		return (-1);
	if (ft_strcmp(array[0], "export") == 0 && array[1] == NULL)
	{
		c_env = copy_env(env);
		sort_ascii_order(c_env);
		print_export(c_env);
	}
	while (array[i])
	{
		elements = ft_split(array[i], '=');
		if (!elements)
			ft_exit_int(-1);
		add_var_and_param(env, elements[0], elements[1]);
		free(elements[0]);
		free(elements[1]);
		free(elements);
		i++;
	}
	return (0);
}
