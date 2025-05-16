/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:08:45 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/11 13:56:52 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "minishell.h"

int	ft_unset(char **array);

int	ft_unset(char **array)
{
	size_t		i;
	t_var		**temp;
	t_env_vars	*env;

	i = 0;
	env = get_env();
	if (!env || !array)
		return (-1);
	if (FOLLOW_ZSH == 1 && array[0] == NULL)
		ft_putstr_fd("unset: not enough arguments\n", 2);
	temp = &env->head_var;
	while (array && array[i] != NULL)
	{
		supp_var(temp, array[i]);
		temp = &env->head_var;
		i++;
	}
	return (0);
}
