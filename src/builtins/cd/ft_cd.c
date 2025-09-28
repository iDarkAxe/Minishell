/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:43:42 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/28 16:21:56 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_printf.h"
#include "garbage.h"
#include "minishell.h"
#include <errno.h>
#include <limits.h>
#include <string.h>

static int	check_args(t_data *data, t_env_vars *env, char **array);

/**
 * @brief Implementation of cd builtin of shell
 *
 * @param data data structure
 * @param array array of strings
 * @return int 0 OK, 1 otherwise
 */
int	ft_cd(t_data *data, char **array)
{
	char	path[PATH_MAX];
	int		ret;

	ret = check_args(data, &data->env, array);
	if (ret == 0)
		return (0);
	else if (ret < 0)
		return (-ret);
	if (getcwd(path, PATH_MAX) == NULL)
	{
		ret = errno;
		ft_dprintf(2, "minishell : cd : modify CWD : OLDPWD : %s\n",
			strerror(ret));
		return (1);
	}
	ret = chdir(array[0]);
	if (ret != 0)
	{
		ret = errno;
		ft_dprintf(2, "minishell: cd: %s: %s\n", array[0], strerror(ret));
		return (1);
	}
	change_cwd_oldpwd(data, path);
	change_cwd(data, 1);
	return (0);
}

/**
 * @brief Check if args are valid are not
 *
 * @param array array of strings
 * @return int 0 and 1 OK, -1 is error
 */
static int	check_args(t_data *data, t_env_vars *env, char **array)
{
	if (array == NULL || array[0] == NULL)
		return (change_cwd_to_home(data, env));
	if (array[1] != NULL)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (-1);
	}
	if (array[0] && (ft_strncmp(array[0], "-", 2) == 0 || ft_strncmp(array[0],
				"--", 3) == 0))
		return (change_cwd_to_previous_cwd(data, env));
	return (1);
}
