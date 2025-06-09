/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:21:20 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/06 19:27:10 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parsing.h"
#include "garbage.h"
#include "libft.h"
#include "data_structure.h"

char	*search_env_str(t_data *data, const char *var, size_t size)
{
	char	*str;
	t_var	*head;

	head = data->env.head_var;
	str = NULL;
	if (*var == '?')
	{
		str = ft_itoa(data->ret);
		return (str);
	}
	while (head != NULL)
	{
		if (ft_strncmp(head->value, var, size) == 0
			&& ft_strlen(head->value) == size)
		{
			str = create_str_with_params(&data->garbage, head->head_params);
			if (!str)
				return (NULL);
			return (str);
		}
		head = head->next;
	}
	if (head == NULL && str == NULL)
		str = ft_strdup(NULL);
	return (str);
}

size_t	ft_strlen_ignore_quote(char *str)
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
	size_t	size_trad_var;

	result = NULL;
	size_trad_var = 0;
	if (*str == '"' || *str == '\'')
	{
		size = ft_strlen_ignore_quote(str);
		result = ft_strcpy_var_trad(data, str, size);
		if (size == 0)
			result = ft_strdup("");
	}
	else
		result = search_env_str(data, str, size);
	return (result);
}

static void	setup_quote(char *str, char *quote, t_bool *is_expandable)
{
	if (*quote == 0 && *str == '"')
	{
		*quote = *str;
		*is_expandable = TRUE;
	}
	else if (*quote == 0 && *str == '\'')
	{
		*quote = *str;
		*is_expandable = FALSE;
	}
	else if (*quote == *str)
	{
		*is_expandable = TRUE;
		*quote = 0;
	}
	str++;
	if (*str != '\'' && *str != '"')
		return ;
	setup_quote(str, quote, is_expandable);
}

static t_bool detect_dollars(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_expandable(char *str)
{
	size_t	i;
	char	quote;
	t_bool	is_expandable;

	i = 0;
	quote = 0;
	is_expandable = TRUE;
	if (detect_dollars(str) == FALSE)
		return (FALSE);
	while (str[i] && str[i] != '\'' && str[i] != '"' && str[i] != '$')
		i++;
	if (str[i] == '$')
		return (TRUE);
	setup_quote(&str[i], &quote, &is_expandable);
	if (is_expandable == TRUE)
		return (TRUE);
	return (FALSE);
}
