/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:43:42 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/28 16:21:22 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "builtins.h"
#include "ft_printf.h"
#include <errno.h>
#include <limits.h>
#include <string.h>

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
	int		error;

	if (is_pwd == 1)
		var = "PWD=";
	else
		var = "OLDPWD=";
	if (getcwd(path, PATH_MAX) == NULL)
	{
		error = errno;
		ft_dprintf(2, "minishell : cd : modify CWD : %s : %s\n", var,
			strerror(error));
		return ;
	}
	export_arg = ft_strjoin(var, path);
	if (export_arg == NULL)
		ft_exit_int_np(&data->garbage, 1);
	add_to_garbage(&data->garbage, export_arg);
	ft_export(data, (char *[]){export_arg, NULL});
	free_element_gb(&data->garbage, export_arg);
}

/**
 * @brief Change OLDPWD with prev_path
 * 
 * @param[in,out] data data structure
 * @param[in,out] prev_path previous path
 */
void	change_cwd_oldpwd(t_data *data, char *prev_path)
{
	char	*export_arg;

	export_arg = ft_strjoin("OLDPWD=", prev_path);
	if (export_arg == NULL)
		ft_exit_int_np(&data->garbage, 1);
	add_to_garbage(&data->garbage, export_arg);
	ft_export(data, (char *[]){export_arg, NULL});
	free_element_gb(&data->garbage, export_arg);
}

/**
 * @brief Change the current working directory to the previous CWD
 *
 * @param env environment shell
 * @return int 0 OK, error otherwise
 */
int	change_cwd_to_home(t_data *data, t_env_vars *env)
{
	t_var	*var;
	char	*path;

	path = NULL;
	var = search_env_var(env, "HOME", ft_strlen("HOME"));
	if (!var || !var->head_params || !var->head_params->value)
		ft_dprintf(2, "minishell: cd: HOME not set\n");
	if (var && var->head_params)
		path = var->head_params->value;
	if (path == NULL)
		return (-1);
	change_cwd(data, 0);
	chdir(path);
	change_cwd(data, 1);
	return (0);
}

/**
 * @brief Change the current working directory to the previous CWD
 *
 * @param env environment shell
 * @return int 0 OK, error otherwise
 */
int	change_cwd_to_previous_cwd(t_data *data, t_env_vars *env)
{
	t_var	*var;
	char	*path;
	int		ret;

	path = NULL;
	var = search_env_var(env, "OLDPWD", ft_strlen("OLDPWD"));
	if (!var || !var->head_params || !var->head_params->value)
		ft_dprintf(2, "minishell: cd: OLDPWD not set\n");
	if (var && var->head_params)
		path = var->head_params->value;
	if (path == NULL)
		return (-1);
	change_cwd(data, 0);
	ft_printf("%s\n", path);
	ret = chdir(path);
	if (ret != 0)
	{
		ret = errno;
		ft_dprintf(2, "minishell: cd: %s: %s\n", path, strerror(ret));
		return (1);
	}
	change_cwd(data, 1);
	return (0);
}
