/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:29:10 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/02 17:09:04 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_data *data, char *envp[])
{
	int	i;

	i = 0;
	while (envp && envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			if (ft_strlen(envp[i]) > 5)
				return (envp[i]);
			else
				data->path_is_empty = TRUE;
		}
		i++;
	}
	return (NULL);
}

char	**get_path_bins(t_data *data, char *envp[])
{
	char	*path;
	char	**all_paths_bins;

	path = get_path(data, envp);
	if (!path)
		return (NULL);
	all_paths_bins = ft_split(path, ':');
	if (!all_paths_bins)
		return (NULL);
	return (all_paths_bins);
}

char	*get_command_with_path(t_data *data, char *command, char **all_paths)
{
	size_t	i;
	char	*path_bin;

	i = 0;
	path_bin = NULL;
	while (all_paths_bins[i])
	{
		path_bin = ft_strjoins((char *[]){all_paths_bins[i], "/",
				data.command.toks[0]});
		if (!path_bin)
		{
			free_double_array(all_paths_bins);
			exit(EXIT_FAILURE);
		}
		if (access(path_bin, X_OK) == -1)
		{
			free(path_bin);
			i++;
		}
		else
			return (path_bin);
	}
	return (NULL);
}
