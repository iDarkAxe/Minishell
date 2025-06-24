/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:45:33 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/18 11:57:12 by lud-adam         ###   ########.fr       */
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

void	create_last_tokens_var(t_garbage *garbage, t_env_vars *env)
{
	t_var	*last_tokens_var;

	last_tokens_var = search_env_var(env, "_", 1);
	if (last_tokens_var)
		return ;
	last_tokens_var = get_var(garbage, "_");
	if (!last_tokens_var)
		return ;
	last_tokens_var->head_params = get_param(garbage, "minishell", TRUE);
	if (!last_tokens_var->head_params)
		return ;
	ft_varsadd_back(&env->head_var, last_tokens_var);
	return ;
}

static	char	*choose_content(t_data	*data)
{
	t_token		*temp;
	t_command	*temp_command;
	char		*str2;

	if (!data || !data->command)
		return (NULL);
	temp_command = data->command;
	while (temp_command->next != NULL)
		temp_command = temp_command->next;
	temp = temp_command->tokens;
	while (temp->next != NULL)
		temp = temp->next;
	str2 = ft_strdup(temp->str);
	return (str2);
}

/**
 * @brief update_last_token function to update _ var
 */
void	update_last_token(t_data *data)
{
	char	*str;
	char	*str2;

	str2 = choose_content(data);
	if (!str2)
		return ;
	str = ft_strjoin("_=", str2);
	if (!str)
	{
		ft_dprintf(2,
			"minishell: malloc: Critical error of malloc, exiting.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	ft_export(data, (char *[]){str, NULL});
	free(str);
	if (data->last_token)
		free_element_gb(&data->garbage, data->last_token);
	data->last_token = str2;
	if (!data->last_token)
	{
		ft_dprintf(2,
			"minishell: malloc: Critical error of malloc, exiting.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	add_to_garbage(&data->garbage, data->last_token);
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
	shlvl = search_env_var(env, "SHLVL", ft_strlen("SHLVL"));
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
