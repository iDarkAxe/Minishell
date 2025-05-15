/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:45:33 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/14 18:06:19 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "libft.h"

void	create_shlvl(t_env_vars *env)
{
	t_var	*shlvl;

	shlvl = get_var("SHLVL");
	if (!shlvl)
		return ;
	shlvl->head_params = get_param("1", TRUE);
	if (!shlvl->head_params)
		return ;
	ft_varsadd_back(&env->head_var, shlvl);
	return ;
}

void	update_shlvl(void)
{
	t_env_vars *env;
	t_var	*shlvl;
	int		temp;
	char	*temp_1;
	int		size;

	env = get_env();
	shlvl = search_env_var(env, "SHLVL");
	if (!shlvl)
	{
		create_shlvl(env);
		return ;
	}
	temp = ft_atoi(shlvl->head_params->value);
	temp++;
	temp_1 = ft_itoa(temp);
	if (!temp_1)
		return ;
	size = ft_strlen(temp_1);
	free_element_gb(shlvl->head_params->value);
	shlvl->head_params->value = malloc_gb(sizeof(char) * size);
	if (!shlvl->head_params->value)
		return ;
	shlvl->head_params->value = temp_1;
}
