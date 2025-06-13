/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:05:11 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 13:45:24 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_printf.h"
#include "garbage.h"
#include "libft.h"
#include "parsing.h"

/**
 * @brief build_string allow to write the quotes of str
 * @param str string to copy, i reference of i to keep tack position inside str 
 * @return string contains quotes 
 */
static char	*build_string(t_data *data, char *str, size_t *i)
{
	char	*temp;
	size_t	size;

	temp = NULL;
	size = 0;
	while (str[*i] && (str[*i] == '"' || str[*i] == '\''))
	{
		(*i)++;
		size++;
	}
	temp = ft_strndup(&str[*i - size], size);
	if (!temp)
	{
		ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	return (temp);
}

/**
 * @brief expand var allow to expand
 *
 * @param data data structure
 * @param str string
 * @param i index referencing the position of reading
 * @param quote_pointer value of quote pointer
 * @return var environment expand
 */
static char	*expand_var(t_data *data, char *str, size_t *i, char *quote_pointer)
{
	char	*result;
	char	*temp;
	size_t	size;

	size = 0;
	result = NULL;
	while (str[*i] && str != quote_pointer)
	{
		size = compute_size_expand_var(&str[*i]);
		temp = ft_strndup(&str[*i], size);
		if (!temp)
		{
			ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		}
		if (detect_dollar_str(temp) == TRUE)
			expand_and_fill_result(data, &result, temp, size);
		else
			result = fill_string(result, temp);
		free(temp);
		*i += size;
	}
	return (result);
}

/**
 * @brief expand_variables_with_quotes allow to expand with quotes
 *
 * @param data data structure
 * @param str to expand 
 * @return string expand with quotes
 */
static char	*expand_variables_with_quotes(t_data *data, char *str)
{
	size_t	i;
	char	*temp;
	char	*result;
	char	*quote_pointer;

	i = 0;
	result = NULL;
	quote_pointer = NULL;
	if (detect_quote(str) == TRUE && (str[0] == '\'' || str[0] == '"'))
	{
		quote_pointer = ft_strrchr(str, '"');
		temp = build_string(data, str, &i);
		result = fill_string(result, temp);
		free(temp);
	}
	temp = expand_var(data, str, &i, quote_pointer);
	result = fill_string(result, temp);
	free(temp);
	if (detect_quote(str) == TRUE)
	{
		temp = build_string(data, str, &i);
		result = fill_string(result, temp);
		free(temp);
	}
	return (result);
}

/**
 * @brief fill_result fill the char **result 
 *
 * @param data data structure
 * @param result array of strings
 * @param temp current string
 */
static void	fill_result(t_data *data, char **result, char *temp)
{
	char	*temp_1;

	temp_1 = NULL;
	if (is_expandable(temp) == TRUE)
	{
		temp_1 = expand_variables_with_quotes(data, temp);
		free(temp);
		if (!temp_1)
		{
			ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		}
		*result = fill_string(*result, temp_1);
		free(temp_1);
	}
	else
	{
		*result = fill_string(*result, temp);
		free(temp);
	}
}

/**
 * @brief expand_str allows to expand variables
 *
 * @param str string to expand 
 * @return string expand with quotes
 */
char	*expand_str(t_data *data, char *str)
{
	char	*result;
	char	*temp;
	size_t	size;

	result = NULL;
	temp = NULL;
	size = 0;
	while (str && *str)
	{
		size = compute_size(str);
		if (size != 0)
		{
			temp = ft_strndup(str, size);
			if (!temp)
			{
				ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
				ft_exit_int_np(&data->garbage, EXIT_FAILURE);
			}
			fill_result(data, &result, temp);
			str += size;
		}
		else
			str++;
	}
	return (result);
}
