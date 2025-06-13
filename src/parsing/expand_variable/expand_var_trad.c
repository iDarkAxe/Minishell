/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_trad.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:23:52 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 16:09:59 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"
#include "garbage.h"
#include "parsing.h"

/**
 * @brief expand_and_fill_result
 *
 * @param result string to fill, str string allow to fill result, 
 * size character allow to do the strdup
 */
void	expand_and_fill_result(t_data *data, char **result, char *str,
		size_t size)
{
	char	*temp;

	temp = expand_or_trad_var(data, str, size);
	if (!temp)
	{
		ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	*result = fill_string(*result, temp);
	free(temp);
}

/**
 * @brief ft_strlen_ignore_quote
 *
 * @param str to compute size
 * @return size of str 
 * */
static size_t	ft_strlen_ignore_quote(char *str, char quote)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str && str[i])
	{
		if (str[i] != quote)
			size++;
		i++;
	}
	size++;
	return (size);
}

/**
 * @brief expand_or_trad_var expand the translatable variables
 *
 * @param str to expand, size give the size of str
 * @return size of str 
 * */
char	*expand_or_trad_var(t_data *data, char *str, size_t size)
{
	char	*result;
	size_t	size_ignore_quote;

	if (ft_strlen(str) <= 4 && str[0] == '$'
		&& (str[1] == '"' || str[1] == '\'')
		&& (str[2] == '$' || str[2] == '\0'))
		result = ft_strdup("$");
	else if (str[1] == '"' || str[1] == '\'')
	{
		size_ignore_quote = ft_strlen_ignore_quote(str + 1, str[1]);
		result = ft_strndup(str + 1, size_ignore_quote);
	}
	else
	{
		result = search_env_str(data, str + 1, size - 1);
		if (!result)
			return (strdup_and_check_malloc(&data->garbage));
	}
	if (!result)
	{
		ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	return (result);
}
