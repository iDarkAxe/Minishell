/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:08:45 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/30 10:36:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "ft_printf.h"
#include "minishell.h"

int	ft_unset(t_data *data, char **array);

int	ft_unset(t_data *data, char **array)
{
	size_t		i;
	t_var		**temp;
	t_env_vars	*env;

	i = 0;
	env = &data->env;
	if (!env || !array)
		return (-1);
	if (FOLLOW_ZSH == 1 && array[0] == NULL)
		ft_dprintf(2, "unset: not enough arguments\n");
	temp = &env->head_var;
	while (array && array[i] != NULL)
	{
		supp_var(&data->garbage, temp, array[i]);
		temp = &env->head_var;
		i++;
	}
	return (0);
}
