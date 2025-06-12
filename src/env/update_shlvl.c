/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>        +  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:45:33 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/12 22:33:57 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "libft.h"
#include "data_structure.h"

static void	create_shlvl(t_garbage *garbage, t_env_vars *env);

/**
 * @brief create_shlvl function to create shlvl if not exist 
 *
 * @param env environment to put shlvl inside
 * @return
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
 * @brief update_shlvl function to update the shell lvl
 *
 * @param env environment to search shlvl and update 
 * @return
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
