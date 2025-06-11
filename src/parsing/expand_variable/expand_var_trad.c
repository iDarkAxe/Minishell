/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_trad.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:23:52 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/11 18:34:35 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "garbage.h"
#include "ft_printf.h"
#include "builtins.h"

static size_t	ft_strlen_ignore_quote(char *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != '"' || str[i] == '\'')
			size++;
		i++;
	}
	return (size);
}

static char	*ft_strcpy_var_trad(t_data *data, char *str, size_t size)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
	{
		ft_dprintf(2, "minishell: malloc: Critical error of malloc.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	while (str[i])
	{
		if (str[i] != '"' || str[i] == '\'')
		{
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

char	*expand_or_trad_var(t_data *data, char *str, size_t size)
{
	char	*result;
	size_t	size_ignore_quote;

	result = NULL;
	size_ignore_quote = 0;
	if (str[1] == '"' || str[1] == '\'')
	{
		size_ignore_quote = ft_strlen_ignore_quote(str + 1);
		result = ft_strcpy_var_trad(data, str + 1, size_ignore_quote);
		if (size_ignore_quote == 0)
			result = ft_strdup("");
	}
	else
		result = search_env_str(data, str + 1, size - 1);
	return (result);
}
