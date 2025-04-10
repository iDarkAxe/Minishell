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
	// char *temp;
	char *new_str;

	// temp = string_pre_cleaning(str);
	// if (!temp)
	// 	return (NULL);
	new_str = clean_string(str);
	if (!new_str)
	{
		// free(temp);
		return (NULL);
	}
	// free(temp);
	return (new_str);
}
