/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:43:42 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/23 16:40:30 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*handle_home_path(char *path);
static int	check_args(char **array);

// TODO if env -i : `~` doesn't work
// TODO should update OLDPWD and PWD

int	ft_cd(char **array)
{
	int		ret;
	char	*path;

	ret = check_args(array);
	if (ret == 0)
		return (0);
	else if (ret < 0)
		return (1);
	path = handle_home_path(array[1]);
	if (path != NULL)
		ret = chdir(path);
	else
		ret = chdir(array[1]);
	if (path != NULL)
		free_element_gb(path);
	if (ret != 0)
	{
		print_fd(2, "minishell: cd: '");
		print_fd(2, array[1]);
		perror("'");
		return (1);
	}
	return (0);
}

static int	check_args(char **array)
{
	if (array == NULL || array[1] == NULL)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	if (ft_strncmp(array[1], "-", 2) == 0)
	{
		chdir(getenv("OLDPWD"));
		return (0);
	}
	if (array[2] != NULL)
	{
		print_fd(2, "bash: cd: too many arguments\n");
		return (-1);
	}
	return (1);
}

static char	*handle_home_path(char *path)
{
	char	*home;
	char	*new_path;

	if (path == NULL || path[0] != '~' || ft_strchr(path, '~') == NULL)
		return (NULL);
	home = getenv("HOME");
	if (home == NULL)
		return (NULL);
	new_path = ft_strjoin(home, path + 1);
	if (new_path == NULL)
		return (NULL);
	add_to_garbage(new_path);
	return (new_path);
}

// TODO : Work only at startup because it's not updated

/**
 * @brief Print the current working directory
 *
 * @return int
 */
int	ft_pwd(char **array)
{
	char	*path;

	if (array == NULL || array[1] != NULL)
	{
		print_fd(2, "minishell: pwd: too many arguments\n");
		return (1);
	}
	path = getenv("PWD");
	if (path == NULL)
	{
		print_fd(2, "minishell: pwd: PWD not set\n");
		return (1);
	}
	print_fd(1, path);
	print_fd(1, "\n");
	return (0);
}
