/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:49:27 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/10 14:06:27 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "pipex.h"
#include "parsing.h"
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*parsing_minishell(const char *str)
{
	char	*new_str;
	char	quote;
	int		i;
	int		j;
	int		count;

	if (!str)
		return (NULL);
	quote = 0;
	i = 0;
	j = 0;
	new_str = NULL;
	count = 0;
	if (str[i] == '\'' || str[i] == '"')
		quote = str[i];
	while (str[i])
	{
		if (str[i] == quote)
			count++;
		i++;
	}
	if (count % 2 != 0)
		return (NULL);
	new_str = malloc((ft_strlen(str) - count) * sizeof(char *));
	if (!new_str)
		return (NULL);
	i = 0;
	quote = 0;
	while (str && str[i])
	{
		if (quote == 0 && (str[i] == '"' || str[i] == '\''))
		{
			quote = str[i];
			i++;
		}
		if (quote == '"' && str[i] != '"')
			new_str[j] = str[i];
		else if (quote == '\'')
			new_str[j] = str[i];
		j++;
		i++;
		if (str[i] == quote)
			quote = 0;
	}
	new_str[i] = '\0';
	return (new_str);
}
