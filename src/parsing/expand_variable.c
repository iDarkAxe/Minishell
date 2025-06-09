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

	size = ft_strlen(&str[*i]);
	*i += size;
	temp = ft_strndup(&str[*i - size], size);
	if (!temp)
	{
		ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	temp_1 = expand_or_trad_var(data, temp, size);
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
	temp = expand_var(data, str, &i);
	result = fill_string(result, temp);
	temp = build_string(data, str, &i);
	result = fill_string(result, temp);
	return (result);
}

static void	fill_result(t_data *data, char **result, char *temp)
{
	char	*temp_1;

	temp_1 = NULL;
	if (is_expandable(temp))
	{
		temp_1 = expand_variables_with_quotes(data, temp);
		if (!temp_1)
		{
			ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		}
		free(temp);
		*result = fill_string(*result, temp_1);
	}
	else
		*result = fill_string(*result, temp);
}

char	*expand_str(t_data *data, char *str)
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
		size = ft_strlen_ignore_first_dollar(&str[i], '$');
		if (size != 0)
		{
			temp = ft_strndup(&str[i], size);
			if (!temp)
			{
				ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
				ft_exit_int_np(&data->garbage, EXIT_FAILURE);
			}
			printf("temp : %s\n", temp);
			fill_result(data, &result, temp);
			i += size;
		}
		else
			i++;
	}
	return (result);
}
