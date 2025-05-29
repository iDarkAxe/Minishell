/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:43:42 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/29 11:00:33 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include <linux/limits.h>
#include <limits.h>

int	ft_pwd(t_data *data, char **array);

/**
 * @brief Print the current working directory
 *
 * @return int
 */
int	ft_pwd(t_data *data, char **array)
{
	char	path[PATH_MAX];

	(void)data;
	if (FOLLOW_ZSH == 1 && (array == NULL || array[0] != NULL))
	{
		print_fd(2, "minishell: pwd: too many arguments\n");
		return (1);
	}
	if (getcwd(path, PATH_MAX) == NULL)
	{
		perror("minishell : ");
		return (1);
	}
	print_fd(1, path);
	print_fd(1, "\n");
	return (0);
}
