/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:56:38 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/30 11:08:41 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "data_structure.h"

/**
 * @defgroup Builtins Builtins Functions
 * @brief Implementation of builtins of a shell
 * @{
 */
int								ft_exit(t_data *data, char **array);
int								ft_echo(t_data *data, char **array);
int								ft_which(t_data *data, char **array);
int								ft_export(t_data *data, char **array);
int								ft_env(t_data *data, char **array);
int								ft_unset(t_data *data, char **array);
int								ft_pwd(t_data *data, char **array);
int								ft_cd(t_data *data, char **array);
/** @} */

/**
 * @defgroup Exit Exit Functions
 * @brief Functions for exiting
 * @{
 */
void							ft_exit_int(t_garbage *garbage, int value);
void							ft_exit_int_np(t_garbage *garbage, int value);
/** @} */

/**
 * @defgroup CD CD Functions
 * @brief Functions for CD (change directory)
 * @{
 */
void							change_cwd(t_data *data, t_bool is_pwd);
int								change_cwd_to_home(t_env_vars *env);
int								change_cwd_to_previous_cwd(t_env_vars *env);
/** @} */

#endif
