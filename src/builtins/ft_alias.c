/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:44:33 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/28 17:05:36 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_printf.h"

int	ft_alias(t_data *data, char **array)
{
	size_t	index;
	int		ret;

	if (!data || !array)
		return (1);
	if (!array[0])
		return (0);
	index = 0;
	ret = 0;
	while (array[index] != NULL)
	{
		if (ft_strrchr(array[index], '=') != NULL)
			ft_printf("Modifying %s\n", array[index]);
		else if (0) /* Searching alias in env like structure */
			ft_printf("alias %s='%s'\n", array[index], "remplir");
		else /*n'existe pas*/
		{
			ft_dprintf(2, "minishell: alias: %s: not found\n", array[index]);
			ret = 1;
		}
		index++;
	}
	return (ret);
}
