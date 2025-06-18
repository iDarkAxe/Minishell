/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:45:33 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 13:43:44 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_printf.h"
#include "garbage.h"
#include "libft.h"
#include "builtins.h"
#include "data_structure.h"

static void	create_shlvl(t_garbage *garbage, t_env_vars *env);

/**
 * @brief create_shlvl function to create shlvl if not exist 
 *
 * @param garbage garbage structure
 * @param env environment to put shlvl inside
 */
static void	create_shlvl(t_garbage *garbage, t_env_vars *env)
{
	t_var	*shlvl;

	shlvl = get_var(garbage, "SHLVL");
	if (!shlvl)
		return ;
	shlvl->head_params = get_param(garbage, "1", TRUE);
	if (!shlvl->head_params)
		return ;
	ft_varsadd_back(&env->head_var, shlvl);
	return ;
}

/**
 * @brief update_last_token function to update _ var
 */
void	update_last_token(t_data *data)
{
	t_token	*temp;
	char	*str;

	temp = data->command->tokens;
	while (1)
	{
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	str = ft_strjoin("_=",temp->str);
	if (!str)
	{
		ft_dprintf(2,
			"minishell: malloc: Critical error of malloc, exiting.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	ft_export(data, (char *[]){str, NULL});
	free(str);
}

/**
 * @brief update_shlvl function to update the shell lvl
 *
 * @param env environment to search shlvl and update 
 */
void	update_shlvl(t_garbage *garbage, t_env_vars *env)
{
	t_var		*shlvl;
	int			var_shlvl_integer;
	char		*var_shlvl_string;

	if (!env)
		return ;
	shlvl = search_env_var(env, "SHLVL");
	if (!shlvl)
	{
		create_shlvl(garbage, env);
		return ;
	}
	var_shlvl_integer = ft_atoi(shlvl->head_params->value);
	var_shlvl_integer++;
	var_shlvl_string = ft_itoa(var_shlvl_integer);
	if (!var_shlvl_string)
		return ;
	free_element_gb(garbage, shlvl->head_params->value);
	shlvl->head_params->value = ft_strdup_gb(garbage, var_shlvl_string);
	free(var_shlvl_string);
	if (!shlvl->head_params->value)
		return ;
}
