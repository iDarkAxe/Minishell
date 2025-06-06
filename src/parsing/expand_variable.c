/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>        +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:05:11 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/05 18:34:55 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_printf.h"
#include "garbage.h"
#include "libft.h"
#include "parsing.h"

static char	*build_string(t_data *data, char *str, size_t *i)
{
	char	*temp;
	size_t	size;

	temp = NULL;
	size = 0;
	while (str[*i] && str[*i] != '$')
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
	(*i)++;
	return (temp);
}

static char	*expand_var(t_data *data, char *str, size_t *i)
{
	char	*temp;
	char	*temp_1;
	size_t	size;

	size = 0;
	while (str[*i] && ft_isalpha(str[*i]) == 1)
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
	temp_1 = search_env_str(&data->garbage, &data->env, temp, ft_strlen(temp));
	if (!temp_1)
	{
		ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	free(temp);
	return (temp_1);
}

static char	*expand_variables_with_quotes(t_data *data, char *str)
{
	size_t	i;
	char	*temp;
	char	*result;

	i = 0;
	result = NULL;
	temp = build_string(data, str, &i);
	result = fill_string(result, temp);
	free(temp);
	temp = expand_var(data, str, &i);
	result = fill_string(result, temp);
	free(temp);
	temp = build_string(data, str, &i);
	result = fill_string(result, temp);
	free(temp);
	return (result);
}

static void	setup_quote(char *str, char *quote)
{
	if (*quote == '0' && (*str == '"' || *str == '\''))
		*quote = *str;
	else if (*quote == *str)
		*quote = '0';
}

static void	fill_result(t_data *data, char **result, char *temp, char *quote)
{
	char	*temp_1;

	temp_1 = NULL;
	if (is_expandable(temp, *quote))
	{
		temp_1 = expand_variables_with_quotes(data, temp);
		if (!temp_1)
		{
			ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		}
		free(temp);
		*result = fill_string(*result, temp_1);
		free(temp_1);
	}
	else
	{
		*result = fill_string(*result, temp);
		free(temp);
	}
}

char	*expand_str(t_data *data, char *str, char *quote)
{
	char	*result;
	char	*temp;
	size_t	i;
	size_t	size;

	result = NULL;
	temp = NULL;
	i = 0;
	size = 0;
	while (str[i])
	{
		setup_quote(str, quote);
		size = ft_strlen(&str[i]);
		temp = ft_strndup(&str[i], size);
		if (!temp)
		{
			ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		}
		fill_result(data, &result, temp, quote);
		i += size;
	}
	return (result);
}
