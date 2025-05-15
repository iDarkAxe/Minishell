/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:56:38 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/11 13:46:21 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int								ft_exit(char **array);
void							ft_exit_int(int value);
void							ft_exit_int_np(int value);
int								ft_echo(char **array);
int								ft_which(char **array);
int								ft_export(char **array);
int								ft_env(char **array);
int								ft_unset(char **array);
int								ft_cd(char **array);
int								ft_pwd(char **array);

#endif
