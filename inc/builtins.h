/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:56:38 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/03 11:56:51 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int								ft_exit(char **array);
void							ft_exit_int(int value);
int								ft_echo(char **array, char delimitor);
int								ft_which(char **array);
int								ft_export(char **array, char **envp);
int								ft_env(char **envp);
int								ft_unset(char **array, char **envp);
int								ft_cd(char **array);
int								ft_pwd(char **array);
