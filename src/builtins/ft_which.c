/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:34:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/22 14:55:47 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stddef.h>

static int	condition_which(char *str);

/**
 * @brief Says if the command are built-in commands or not
 *
 * @param tokens array of strings
 * @return int 1 if not at least one is not built-in, 0 if all strs built-ins
 */
int	ft_which(char **tokens)
{
	size_t	i;
	int		is_not_builtin;

	if (tokens == NULL || tokens[0] == NULL || tokens[1] == NULL)
		return (1);
	i = 1;
	is_not_builtin = 0;
	while (tokens[i] != NULL)
	{
		if (condition_which(tokens[i]) == 1)
		{
			print_fd(1, tokens[i]);
			print_fd(1, ": minishell built-in command\n");
		}
		else
		{
			is_not_builtin = 1;
			print_fd(2, tokens[i]);
			print_fd(2, ": command not found in built-ins\n");
		}
		i++;
	}
	return (is_not_builtin);
}

/**
 * @brief Search if the string is a builtin command
 *
 * @param str str to check
 * @return int 1 is builtin, 0 if not
 */
static int	condition_which(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0 || ft_strncmp(str, "exit", 4) == 0
		|| ft_strncmp(str, "which", 5) == 0 || ft_strncmp(str, "env", 3) == 0
		|| ft_strncmp(str, "export", 6) == 0 || ft_strncmp(str, "unset", 5) == 0
		|| ft_strncmp(str, "cd", 2) == 0 || ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	return (0);
}
