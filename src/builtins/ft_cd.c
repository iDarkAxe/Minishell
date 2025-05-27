/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:43:42 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/27 11:52:20 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

int			ft_cd(t_data *data, char **array);
static int	check_args(char **array);

int			ft_pwd(t_data *data, char **array);

// TODO if env -i : `~` doesn't work
// TODO should update OLDPWD and PWD

/**
 * @brief Implementatin of cd builtin of shell
 *
 * @param array array of strings
 * @return int 0 OK, 1 otherwise
 */
int	ft_cd(t_data *data, char **array)
{
	int	ret;

	(void)data;
	ret = check_args(array);
	if (ret == 0)
		return (0);
	else if (ret < 0)
		return (ret);
	ret = chdir(array[0]);
	if (ret != 0)
	{
		print_fd(2, "minishell: cd: '");
		print_fd(2, array[0]);
		perror("'");
		return (ret);
	}
	return (0);
}

/**
 * @brief Check if args are valid are not
 *
 * @param array array of strings
 * @return int 0 and 1 OK, -1 is error
 */
static int	check_args(char **array)
{
	char	*path;

	if (array == NULL || array[0] == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
			return (-1);
		chdir(path);
		return (0);
	}
	if (array[0] && ft_strncmp(array[0], "-", 2) == 0)
	{
		path = getenv("OLDPWD");
		if (path == NULL)
			return (-1);
		chdir(path);
		return (0);
	}
	if (array[1] != NULL)
	{
		print_fd(2, "bash: cd: too many arguments\n");
		return (-1);
	}
	return (1);
}

// TODO : Work only at startup because it's not updated

/**
 * @brief Print the current working directory
 *
 * @return int
 */
int	ft_pwd(t_data *data, char **array)
{
	char	path[PATH_MAX];

	(void)data;
	if (array == NULL || array[0] != NULL)
	{
		print_fd(2, "minishell: pwd: too many arguments\n");
		return (1);
	}
	path = getcwd(path, PATH_MAX);
	if (path == NULL)
	{
		perror("Minishell : ");
		return (1);
	}
	print_fd(1, path);
	print_fd(1, "\n");
	return (0);
}
