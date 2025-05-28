/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:43:42 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/28 12:12:57 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "builtins.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

int			ft_cd(t_data *data, char **array);
static int	check_args(char **array);
static void	change_cwd(t_data *data, t_bool is_pwd);

int			ft_pwd(t_data *data, char **array);

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
	change_cwd(data, 0);
	ret = chdir(array[0]);
	if (ret != 0)
	{
		print_fd(2, "minishell: cd: '");
		print_fd(2, array[0]);
		perror("'");
		return (ret);
	}
	change_cwd(data, 1);
	return (0);
}

/**
 * @brief Change the values of ENV VAR
 * 
 * @param data data structure
 * @param is_pwd 1 for PWD, 0 for OLD_PWD 
 */
static void	change_cwd(t_data *data, t_bool is_pwd)
{
	char	*var;
	char	path[PATH_MAX];
	char	*old_path;
	char	*export_arg;

	if (is_pwd == 1)
		var = "PWD=";
	else
		var = "OLDPWD=";
	if (getcwd(path, PATH_MAX) == NULL)
	{
		perror("minishell : modify CWD :");
		return ;
	}
	ft_unset(data, (char *[]){var, NULL});
	old_path = ft_strdup_gb(&data->garbage, path);
	if (old_path == NULL)
		ft_exit_int_np(&data->garbage, 1);
	export_arg = ft_strjoin(var, old_path);
	if (export_arg == NULL)
		ft_exit_int_np(&data->garbage, 1);
	ft_export(data, (char *[]){export_arg, NULL});
	free(export_arg);
	free_element_gb(&data->garbage, old_path);
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
