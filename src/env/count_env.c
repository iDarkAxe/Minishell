/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:27:31 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/02 10:27:43 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	count_env(t_env_vars env)
{
	int	count;

	count = 0;
	if (!env.head_var)
		return (0);
	while (env.head_var)
	{
		count++;
		env.head_var = env.head_var->next;
	}
	return (count);
}
