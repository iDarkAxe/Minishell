/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:08:45 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/02 11:32:39 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "minishell.h"

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
