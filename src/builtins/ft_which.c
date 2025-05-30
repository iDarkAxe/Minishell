/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:34:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/30 11:26:27 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ft_printf.h"
#include <stddef.h>

static int	condition_which(char *str);
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
	char	is_not_builtin;

	if (tokens == NULL || tokens[0] == NULL)
		return (-1);
	(void)data;
	i = 0;
	is_not_builtin = 0;
	while (tokens[i] != NULL)
	{
		if (condition_which(tokens[i]) == 1)
			ft_printf("%s : minishell built-in command\n", tokens[i]);
		else
		{
			is_not_builtin = 1;
			ft_dprintf(2, "%s : command not found in built-ins\n", tokens[i]);
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
	if (ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "exit", 5) == 0
		|| ft_strncmp(str, "which", 6) == 0 || ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "export", 7) == 0 || ft_strncmp(str, "unset", 6) == 0
		|| ft_strncmp(str, "cd", 3) == 0 || ft_strncmp(str, "pwd", 4) == 0)
		return (1);
	return (0);
}
