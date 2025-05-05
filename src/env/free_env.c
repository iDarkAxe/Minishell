/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:12:06 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/05 13:33:22 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"

void	free_params(t_params *element)
{
	t_params	*temp;

	temp = NULL;
	if (!element)
		return ;
	while (element)
	{
		temp = element->next;
		free_element_gb(element->value);
		free_element_gb(element);
		element = temp;
	}
	return ;
}
