/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:50:23 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/15 11:58:34 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>
// TAKE OFF
#include <stdio.h>

t_var	*ft_varlast(t_var *var)
{
	while (var)
	{
		if (var->next == NULL)
			return (var);
		var = var->next;
	}
	return (NULL);
}

void	ft_varsadd_back(t_var **var, t_var *new)
{
	t_var	*pt;

	pt = NULL;
	if (*var == NULL)
	{
		*var = new;
		return ;
	}
	pt = ft_varlast(*var);
	pt->next = new;
}

t_params	*ft_paramlast(t_params *params)
{
	while (params)
	{
		if (params->next == NULL)
			return (params);
		params = params->next;
	}
	return (NULL);
}

void	ft_paramsadd_back(t_params **params, t_params *new)
{
	t_params	*pt;

	pt = NULL;
	if (*params == NULL)
	{
		*params = new;
		new->next = NULL;
		return ;
	}
	pt = ft_paramlast(*params);
	pt->next = new;
}

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
	int			k;

	k = 0;
	if (!str)
		return (NULL);
	new_param = NULL;
	params = NULL;
	while (str[*i] && k < 1000)
	{
		new_param = get_sub_params(str, i);
		new_param->next = NULL;
		if (!new_param)
			return (NULL);
		ft_paramsadd_back(&params, new_param);
		if (str[*i] == ':')
			(*i)++;
		k++;
	}
	return (params);
}

t_env_vars	*get_env(char *envp[])
{
	t_env_vars	*env;
	t_var		*new;
	size_t		i;
	size_t		j;
	size_t		count;

	env = malloc_gb(sizeof(t_env_vars));
	if (!env)
		return (NULL);
	i = 0;
	j = 0;
	count = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		new = malloc_gb(sizeof(t_var));
		if (!new)
			return (NULL);
		new->next = NULL;
		new->value = get_var(envp[i], &j);
		// printf("%s", new->value);
		if (!new->value)
		{
			free_element_gb(new);
			return (NULL);
		}
		j++;
		new->count = count++;
		new->head_params = get_params(envp[i], &j);
		if (!new->head_params)
		{
			free_element_gb(new->value);
			free_element_gb(new);
			continue ;
		}
		ft_varsadd_back(&env->head_var, new);
		i++;
		// if (envp[i] == NULL)
		// 	return (env);
		// t_params	*head;
		//
		// head = new->head_params;
		// printf("%s=", new->value);
		// while (head != NULL)
		// {
		// 	printf("%s", head->value);
		// 	head = head->next;
		// }
		// printf("\n\n\n");
	}
	return (env);
}
