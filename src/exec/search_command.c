/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:32:13 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/03 16:25:45 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	simple_search_command(t_data *data, t_command *command, const char *cmd);
int	search_command(t_data *data, t_command *command, char **tokens);

/**
 * @brief  Search if command is a builtin or not
 *
 * @param data data structure
 * @param command command structure
 * @param tokens array of strings
 * @return int 0 if command found, 1 otherwise
 */
int	search_command(t_data *data, t_command *command, char **tokens)
{
	static char	*command_name[] = {"echo", "env", "which", "unset", "cd",
		"pwd", "exit", "export", NULL};
	static int	(*cmd[])(t_data *, char **) = {ft_echo, ft_env, ft_which,
		ft_unset, ft_cd, ft_pwd, ft_exit, ft_export, NULL};
	size_t		i;

	if (!data || !command || !tokens || !tokens[0])
		return (1);
	i = 0;
	while (command_name[i])
	{
		if (ft_strncmp(tokens[0], command_name[i], ft_strlen(command_name[i])
				+ 1) == 0)
		{
			command->return_value = cmd[i](data, &tokens[1]);
			return (0);
		}
		i++;
	}
	if (command_name[i] == NULL)
		return (-2);
	return (0);
}

/**
 * @brief Search if a command is a builtin
 * 
 * @param data data struture 
 * @param command command structure
 * @param cmd command name
 * @return int 1 is found, 0 is not found
 */
int	simple_search_command(t_data *data, t_command *command, const char *cmd)
{
	static char	*command_name[] = {"echo", "env", "which", "unset", "cd",
		"pwd", "exit", "export", NULL};
	size_t		i;

	if (!data || !command || !cmd)
		return (0);
	i = 0;
	while (command_name[i])
	{
		if (ft_strncmp(cmd, command_name[i], ft_strlen(command_name[i])
				+ 1) == 0)
		{
			return (1);
		}
		i++;
	}
	if (command_name[i] == NULL)
		return (0);
	return (0);
}
