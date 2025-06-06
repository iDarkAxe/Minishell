/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:43:27 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/05 13:52:24 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen_two_quotes(const char *str, char quote)
{
	size_t	count_quote;
	size_t	size;

	count_quote = 0;
	size = 0;
	while (str && *str)
	{
		size++;
		if (*str == quote)
			count_quote++;
		if (count_quote == 2)
			return (size);
		str++;
	}
	return (size);
}

size_t	compute_size(const char *str, char quote)
{
	size_t	size;
	size_t	i;

	size = ft_strlen(str);
	return (size);
}

char	*setup_string(t_data *data, char *str)
{
	char	*str_expanded;
	char	quote;

	quote = '0';
	str_expanded = expand_str(data, str, &quote);
	if (!str_expanded)
		return (NULL);
	printf("expand_str : %s\n", str_expanded);
	add_to_garbage(&data->garbage, str_expanded);
	if (quote != '0')
	{
		ft_dprintf(2, "minishell: syntax error: Unclosed quote: `%c'\n", quote);
		// WARNING CAUSE SEGFAULT BECAUSE DATA COMMAND NO UNINITIALIZED
		// data->command->return_value = 2;
		// data->command->parse_error = 1;
		return (NULL);
	}
	return (str_expanded);
}
