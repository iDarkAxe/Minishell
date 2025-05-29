/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:43:42 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/29 12:51:44 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include "builtins.h"
#include "env.h"
#include <linux/limits.h>
#include <limits.h>

static int	check_args(t_env_vars *env, char **array);

/**
 * @brief Implementatin of cd builtin of shell
 *
 * @param array array of strings
 * @return int 0 OK, 1 otherwise
 */
int	ft_cd(t_data *data, char **array)
{
	int	ret;

	ret = check_args(&data->env, array);
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
void	change_cwd(t_data *data, t_bool is_pwd)
{
	char	*var;
	char	*export_arg;
	char	path[PATH_MAX];

	if (is_pwd == 1)
		var = "PWD=";
	else
		var = "OLDPWD=";
	if (getcwd(path, PATH_MAX) == NULL)
	{
		perror("minishell : modify CWD :");
		return ;
	}
	export_arg = ft_strjoins((char *[]){var, path, NULL});
	if (export_arg == NULL)
		ft_exit_int_np(&data->garbage, 1);
	ft_export(data, (char *[]){export_arg, NULL});
	free(export_arg);
}

/**
 * @brief Check if args are valid are not
 *
 * @param array array of strings
 * @return int 0 and 1 OK, -1 is error
 */
static int	check_args(t_env_vars *env, char **array)
{
	if (array == NULL || array[0] == NULL)
		return (change_cwd_to_home(env));
	if (array[0] && ft_strncmp(array[0], "-", 2) == 0)
		return (change_cwd_to_previous_cwd(env));
	if (array[1] != NULL)
	{
		print_fd(2, "bash: cd: too many arguments\n");
		return (-1);
	}
	return (1);
}

int	change_cwd_to_home(t_env_vars *env)
{
	t_var	*var;
	char	*path;

	path = NULL;
	var = search_env_var(env, "HOME");
	if (!var || !var->head_params || !var->head_params->value)
		print_fd(2, "minishell: cd: HOME not set\n");
	if (var && var->head_params)
		path = var->head_params->value;
	if (path == NULL)
		return (-1);
	chdir(path);
	return (0);
}

int	change_cwd_to_previous_cwd(t_env_vars *env)
{
	t_var	*var;
	char	*path;

	path = NULL;
	var = search_env_var(env, "OLDPWD");
	if (!var || !var->head_params || !var->head_params->value)
		print_fd(2, "minishell: cd: OLDPWD not set\n");
	if (var && var->head_params)
		path = var->head_params->value;
	if (path == NULL)
		return (-1);
	chdir(path);
	return (0);
}
