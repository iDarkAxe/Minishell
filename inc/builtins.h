/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:56:38 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/26 17:42:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "data_structure.h"

int								ft_exit(t_data *data, char **array);
void							ft_exit_int(t_garbage *garbage, int value);
void							ft_exit_int_np(t_garbage *garbage, int value);
int								ft_echo(t_data *data, char **array);
int								ft_which(t_data *data, char **array);
int								ft_export(t_data *data, char **array);
int								ft_env(t_data *data, char **array);
int								ft_unset(t_data *data, char **array);
int								ft_cd(t_data *data, char **array);
int								ft_pwd(t_data *data, char **array);

#endif
