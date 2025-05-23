/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:56:38 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/23 12:12:20 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "data_structure.h"

int								ft_exit(char **array);
void							ft_exit_int(t_garbage *garbage, int value);
// FIXME add garbage to exit int np
void							ft_exit_int_np(int value);
int								ft_echo(char **array);
int								ft_which(char **array);
int								ft_export(t_data *data, char **array);
int								ft_env(char **array);
int								ft_unset(char **array);
int								ft_cd(char **array);
int								ft_pwd(char **array);

/* int								ft_exit(t_data *data, char **array);
void							ft_exit_int(t_data *data, int value);
void							ft_exit_int_np(t_data *data, int value);
int								ft_echo(t_data *data, char **array);
int								ft_which(t_data *data, char **array);
int								ft_export(t_data *data, char **array);
int								ft_env(t_data *data, char **array);
int								ft_unset(t_data *data, char **array);
int								ft_cd(t_data *data, char **array);
int								ft_pwd(t_data *data, char **array); */

#endif
