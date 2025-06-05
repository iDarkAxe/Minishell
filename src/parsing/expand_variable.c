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
#include "garbage.h"
#include "ft_printf.h"
#include "libft.h"
#include "parsing.h"

char	*search_env_str(t_garbage *garbage, t_env_vars *env, const char *var,
		size_t size)
{
	char	*str;
	t_var	*head;

	head = env->head_var;
	str = NULL;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, var, size) == 0
			&& ft_strlen(head->value) == size)
		{
			str = create_str_with_params(garbage, head->head_params);
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

// static char	*expand_variables(t_data *data, char **str, size_t *size)
// {
// 	char	*temp;
//
// 	*str += 1;
// 	*size = ft_strlen_charset((*str), "$\'\" ");
// 	if (*size == 0)
// 		return (NULL);
// 	if (**str == '?')
// 		temp = ft_itoa(data->ret);
// 	else
// 		temp = search_env_str(&data->garbage, &data->env, *str, *size);
// 	if (!temp)
// 		return (NULL);
// 	(*str) += *size;
// 	return (temp);
// }

static char	*expand_variables(t_data *data, char *str)
{
	size_t	i;
	size_t	size;
	char	*temp;
	char	*temp_1;
	char	*result;

	i = 0;
	size = 0;
	temp = NULL;
	result = NULL;
	temp_1 = NULL;
	printf("str inside expand : %s\n", str);
	while (str[i] && (str[i] == '\'' || str[i] == '"'))
	{
		i++;
		size++;
	}
	if (size > 0)
	{
		i += size;
		temp = ft_strndup(str, size);
		if (!temp)
		{
			ft_dprintf(2,
				"minishell: malloc: Critical error of malloc, exiting.\n");
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		}
	}
	if (temp)
	{
		result = fill_string(result, temp);
		free(temp);
	}
	while (str[i] && (str[i] != '\'' || str[i] != '"'))
	{
		i++;
		size++;
	}
	temp = ft_strndup(&str[i], size);
	if (!temp)
	{
		ft_dprintf(2,
			"minishell: malloc: Critical error of malloc, exiting.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	i += size;
	printf("temp inside expand variable : %s\n", temp);
	temp_1 = search_env_str(&data->garbage, &data->env, temp, size);
	if (!temp_1)
	{
		ft_dprintf(2,
			"minishell: malloc: Critical error of malloc, exiting.\n");
		ft_exit_int_np(&data->garbage, EXIT_FAILURE);
	}
	result = fill_string(result, temp_1);
	free(temp);
	free(temp_1);
	size = 0;
	while (str[i] && (str[i] == '\'' || str[i] == '"'))
	{
		i++;
		size++;
	}
	if (size > 0)
	{
		temp = ft_strndup(&str[i], size);
		if (!temp)
		{
			ft_dprintf(2,
				"minishell: malloc: Critical error of malloc, exiting.\n");
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		}
	}
	i += size;
	result = fill_string(result, temp_1);
	if (temp)
		free(temp);
	return (result);
}

// static char	*fill_temp(t_data *data, char **str)
// {
// 	char	*temp;
// 	size_t	size;
//
// 	temp = NULL;
// 	if (**str == '$' && (ft_isspace(*(*str + 1)) == *(*str + 1) || *(*str
// 				+ 1) == '\0') && *(*str + 1) != '"')
// 	{
// 		temp = ft_strdup("$");
// 		*str += 1;
// 	}
// 	else if (**str == '$' && (*(*str + 1) == '"' || *(*str + 1) == '\''))
// 	{
// 		size = ft_strlen_charset(*str + 2, "\"\'");
// 		temp = ft_strndup((*str) + 2, size);
// 		*str += (size + 3);
// 	}
// 	else if (**str == '$')
// 		temp = expand_variables(data, str, &size);
// 	else
// 	{
// 		size = ft_strlen_charset(*str, "$");
// 		temp = ft_strndup(*str, size);
// 		*str += size;
// 	}
// 	return (temp);
// }

static t_bool	is_expandable(const char *s, char quote)
{
	size_t	i;

	i = 0;
	printf("inside is_expandable :%s, quote : %c\n", s, quote);
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] != '$')
		return (FALSE);
	i++;
	if (ft_isalpha(s[i]) == 1 || s[i] == '?' || s[i] == '\'' || s[i] == '"')
	{
		if (quote == '0' || quote == '"')
		{
			printf("je suis iciiiiiiiiiiiiiiiiiiiiii");
			return (TRUE);

		}
	}
	printf("\n");
	return (FALSE);
}

char	*expand_str(t_data *data, char *str, char *quote)
{
	char	*result;
	char	*temp;
	char	*temp_1;
	size_t	i;
	size_t	size;

	result = NULL;
	temp = NULL;
	temp_1 = NULL;
	i = 0;
	size = 0;
	while (str[i])
	{
		if (*quote == '0' && (str[i] == '"' || str[i] == '\''))
			*quote = str[i];
		else if (*quote == str[i])
			*quote = '0';
		printf("quote inside str expand : %c\n\n", *quote);
		if (*quote != '0')
		{
			size = compute_size(&str[i], *quote) + 2;
			temp = ft_strndup(&str[i], size);
		}
		else
		{
			size = compute_size(&str[i], *quote);
			temp = ft_strndup(&str[i], size);
		}
		if (!temp)
		{
			ft_dprintf(2, "minishell: malloc: Critical error of malloc, exiting.\n");
			ft_exit_int_np(&data->garbage, EXIT_FAILURE);
		}
		if (is_expandable(temp, *quote))
		{
			temp_1 = expand_variables(data, temp); 
			if (!temp_1)
			{
				ft_dprintf(2, "minishell: malloc: Critical error of malloc, exiting.\n");
				ft_exit_int_np(&data->garbage, EXIT_FAILURE);
			}
			free(temp);
		}
		if (temp)
		{
			result = fill_string(result, temp);
			free(temp);
		}
		else
			result = fill_string(result, temp_1);
		i += size;
		if (*quote == str[i])
			*quote = '0';
	}
	return (result);
}
