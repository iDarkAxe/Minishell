/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:34:29 by ppontet           #+#    #+#             */
/*   Updated: 2026/02/10 09:39:10 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <stddef.h>

static int	condition_which(char *str);
static int	search_command_path(t_data *data, char *cmd, char **all_paths);
int			ft_which(t_data *data, char **tokens);

/**
 * @brief Says if the command are built-in commands or not
 *
 * @param data data structure
 * @param tokens array of strings
 * @return int 1 if not at least one is not built-in, 0 if all strs built-ins
 */
int	ft_which(t_data *data, char **tokens)
{
	size_t	i;
	int		error_occurred;
	char	**all_paths;

	if (tokens == NULL || tokens[0] == NULL)
		return (-1);
	error_occurred = 0;
	all_paths = get_path(data);
	i = 0;
	while (tokens[i] != NULL)
	{
		if (condition_which(tokens[i]) == 1)
			ft_printf("%s : minishell built-in command\n", tokens[i]);
		else if (search_command_path(data, tokens[i], all_paths) == 1)
			error_occurred = 1;
		i++;
	}
	i = 0;
	while (all_paths[i])
	{
		free(all_paths[i]);
		i++;
	}
	free(all_paths);
	return (error_occurred);
}

/**
 * @brief Search if the string is a builtin command
 *
 * @param str str to check
 * @return int 1 is builtin, 0 if not
 */
static int	condition_which(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "exit", 5) == 0
		|| ft_strncmp(str, "which", 6) == 0 || ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "export", 7) == 0 || ft_strncmp(str, "unset", 6) == 0
		|| ft_strncmp(str, "cd", 3) == 0 || ft_strncmp(str, "pwd", 4) == 0)
		return (1);
	return (0);
}

int	search_command_path(t_data *data, char *cmd, char **all_paths)
{
	char	*path;

	if (access(cmd, X_OK) == 0)
	{
		ft_dprintf(1, "%s\n", cmd);
		return (0);
	}
	path = try_all_paths(data, cmd, all_paths);
	if (path == NULL)
	{
		ft_dprintf(2, "%s not found\n", cmd);
		return (1);
	}
	ft_dprintf(1, "%s\n", path);
	free_element_gb(&data->garbage, path);
	return (0);
}
