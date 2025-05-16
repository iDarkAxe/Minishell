/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:32:13 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/08 14:36:52 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int	search_command_exit(t_command *command, char **tokens, int ret);

/**
 * @brief  Search if command is a builtin or not
 *
 * @param command command structure
 * @param tokens array of strings
 * @param ret return value of previous command
 * @return int 0 if command found, 1 otherwise
 */
int	search_command(t_command *command, char **tokens, int ret)
{
	static int	(*cmd[])(char **) = {ft_echo, ft_env, ft_which, ft_export,
		ft_unset, ft_cd, ft_pwd};
	static char	*command_name[] = {"echo", "env", "which", "export", "unset",
		"cd", "pwd"};
	size_t		i;

	if (!command || !tokens || !tokens[0])
		return (1);
	i = 0;
	while (command_name[i])
	{
		if (ft_strncmp(tokens[0], command_name[i], ft_strlen(command_name[i])
				+ 1) == 0)
		{
			command->return_value = cmd[i](&tokens[1]);
			return (0);
		}
		i++;
	}
	if (command_name[i] == NULL)
		return (search_command_exit(command, tokens, ret));
	return (0);
}

static int	search_command_exit(t_command *command, char **tokens, int ret)
{
	if (!command || !command->tokens || !command->tokens->str)
		return (1);
	if (ft_strncmp(tokens[0], "exit", 5) != 0)
		return (2);
	if (tokens && tokens[0] && tokens[1] == NULL)
		ft_exit_int(ret);
	else
		command->return_value = ft_exit(&tokens[1]);
	return (0);
}
