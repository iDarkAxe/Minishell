/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:21:20 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/18 12:54:38 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "libft.h"
#include "data_structure.h"
#include "builtins.h"
#include "ft_printf.h"
#include "parsing.h"
#include "ft_signal.h"

static char	*handle_prev_ret_command_value(int ret);

char	*strdup_and_check_malloc(t_garbage *garbage)
{
	char	*temp;

	temp = ft_strdup(NULL);
	if (temp == NULL)
	{
		ft_dprintf(2,
			"minishell: malloc: Critical error of malloc, exiting.\n");
		ft_exit_int_np(garbage, EXIT_FAILURE);
	}
	return (temp);
}

char	*handle_prev_ret_command_value(int ret)
{
	char	*str;

	if (g_sig != 0)
	{
		str = ft_itoa(g_sig);
		g_sig = 0;
	}
	else
		str = ft_itoa(ret);
	return (str);
}

/**
 * @brief search_env_str search inside env the environment variables
 * @param var variable to search inside env, size var size
 * @return the associate value of var or nothing if not find inside env
 * */
char	*search_env_str(t_data *data, const char *var, size_t size)
{
	char	*str;
	t_var	*head;

	head = data->env.head_var;
	str = NULL;
	if (*var == '?')
		return (handle_prev_ret_command_value(data->ret));
	while (head != NULL)
	{
		if (ft_strncmp(head->value, var, size) == 0
			&& ft_strlen(head->value) == size)
		{
			if (!head->head_params)
				return (NULL);
			str = create_str_with_params(&data->garbage, head->head_params);
			return (str);
		}
		head = head->next;
	}
	if (head == NULL && str == NULL)
		str = strdup_and_check_malloc(&data->garbage);
	return (str);
}

/**
 * @brief setup_quote allow to know if str is expandable
 * @param str string to check, quote detect type of quote, 
 * is_expandable t_bool to say if ex   pandable or not
 * */
static void	setup_quote(char *str, char *quote, t_bool *is_expandable)
{
	if (*quote == '0' && *str == '"')
	{
		*quote = *str;
		*is_expandable = TRUE;
	}
	else if (*quote == '0' && *str == '\'')
	{
		*quote = *str;
		*is_expandable = FALSE;
	}
	else if (*quote == *str)
	{
		*quote = '0';
		*is_expandable = TRUE;
	}
	str++;
	if (ft_isalnum(*str) == 1 || *str == '$' || *str == '?')
		return ;
	setup_quote(str, quote, is_expandable);
}

/**
 * @brief is_expandable detect if the string is expandable
 * @param str string to check if expandable
 * @return TRUE or FALSE 
 * */
t_bool	is_expandable(char *str)
{
	size_t	i;
	char	quote;
	t_bool	is_expandable;

	i = 0;
	quote = '0';
	is_expandable = TRUE;
	if (!str)
		return (FALSE);
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] != '$')
		return (FALSE);
	else if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '"'))
		return (TRUE);
	i++;
	if (ft_isalpha(str[i]) == 1 || str[i] == '?'
		|| str[i] == '\'' || str[i] == '"')
	{
		setup_quote(str, &quote, &is_expandable);
		if (is_expandable == TRUE)
			return (TRUE);
	}
	return (FALSE);
}
