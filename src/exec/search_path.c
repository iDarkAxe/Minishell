/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:40:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/13 13:29:20 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "exec.h"
#include "parsing.h"
#include "ft_printf.h"

static void	search_path(t_data *data, t_command *command);
static void	build_path(t_data *data, t_command *command);
void		search_paths(t_data *data, t_command *command);

static char	**get_path(t_data *data);
char		*try_all_paths(t_data *data, char *cmd, char **all_paths);

/**
 * @brief Search path for the designated command
 * the command needs a path
 *
 * @param data data structure
 * @param command command structure
 */
void	search_path(t_data *data, t_command *command)
{
	char	*cmd;
	char	**all_paths;
	size_t	index;

	if (ft_strncmp(command->tokens->str, "|", 2) == 0)
		cmd = command->tokens->next->str;
	else
		cmd = command->tokens->str;
	all_paths = get_path(data);
	command->path = try_all_paths(data, cmd, all_paths);
	if (all_paths == NULL)
		return ;
	index = 0;
	while (all_paths[index])
	{
		free(all_paths[index]);
		all_paths[index] = NULL;
		index++;
	}
}

static char	**get_path(t_data *data)
{
	size_t	i;
	char	**envp;
	char	**all_path_bins;

	i = 0;
	envp = env_to_array(data);
	while (envp && envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			if (ft_strlen(envp[i]) > 5)
			{
				all_path_bins = ft_split(envp[i], ':');
				free_array(&data->garbage, envp);
				add_to_garbage(&data->garbage, all_path_bins);
				return (all_path_bins);
			}
		}
		i++;
	}
	return (NULL);
}

char	*try_all_paths(t_data *data, char *command, char **all_paths)
{
	size_t	i;
	char	*path_bin;

	i = 0;
	if (!all_paths)
		return (NULL);
	while (all_paths[i])
	{
		path_bin = ft_strjoins((char *[]){all_paths[i], "/", command, NULL});
		if (!path_bin)
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		add_to_garbage(&data->garbage, path_bin);
		if (access(path_bin, X_OK) == -1)
		{
			free_element_gb(&data->garbage, path_bin);
			i++;
		}
		else
			return (path_bin);
	}
	return (NULL);
}

/**
 * @brief Build path for the designated command
 *
 * @param data data structure
 * @param command command structure
 */
void	build_path(t_data *data, t_command *command)
{
	char	*str;

	if (!command || command->path != NULL)
		return ;
	if (!command->tokens || !command->tokens->str)
	{
		command->path = ft_strdup("NULL");
		add_to_garbage(&data->garbage, command->path);
		return ;
	}
	if (ft_strncmp(command->tokens->str, "|", 2) == 0
		|| ft_strncmp(command->tokens->str, ";", 2) == 0)
		str = command->tokens->next->str;
	else
		str = command->tokens->str;
	if (ft_strchr(str, '/') != NULL)
		command->path = str;
	else
		search_path(data, command);
	if (command->path == NULL)
	{
		ft_dprintf(2, "%s: command not found\n", str);
		command->parse_error = 1;
		command->return_value = 127;
	}
}

/**
 * @brief Search Path for all commands
 *
 * @param data data structure
 * @param command command structure
 */
void	search_paths(t_data *data, t_command *command)
{
	t_command	*current;
	char		*str;

	current = command;
	if (is_commands_valid(data) == 0)
		return ;
	while (current)
	{
		if (current->parse_error == 1 || !current->tokens
			|| !current->tokens->str)
			break ;
		if (ft_strncmp(current->tokens->str, "|", 2) == 0)
			str = current->tokens->next->str;
		else
			str = current->tokens->str;
		if (simple_search_command(data, current, str) == 0)
			build_path(data, current);
		current = current->next;
	}
}
