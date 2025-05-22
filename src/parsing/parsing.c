/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:43:27 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/18 09:44:57 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "parsing.h"

size_t			count_without_quote(const char *str);

/**
 * @brief Prototype for parsing
 *
 * @param line line to parse
 * @return char**
 */
char	**parse_line(char *line)
{
	char	**tokens;

	line = parsing_minishell(line);
	tokens = lexer(line);
	if (tokens == NULL)
	{
		free_element_gb(line);
		ft_exit((char *[]){"1", NULL});
	}
	free_element_gb(line);
	tokens = expand_tildes_tokens(tokens);
	if (tokens == NULL)
		ft_exit_int_np(1);
	return (tokens);
}

static char	*fill_result(char *result, char *temp)
{
	char	*temp_result;

	temp_result = NULL;
	if (!result)
	{
		result = ft_strdup(temp);
		if (!result)
			return (NULL);
		free(temp);
		return (result);
	}
	else if (result && temp)
	{
		if (result == temp)
			return (temp);
		temp_result = ft_strdup(result);
		if (!temp_result)
			return (NULL);
		free(result);
		result = ft_strjoin(temp_result, temp);
		if (!result)
			return (NULL);
		free(temp_result);
		free(temp);
	}
	return (result);
}

void	handle_quote(const char *str, char *quote, size_t *i, t_bool *have_to_expand)
{
	// printf("Inside handle quote\n");
	if (*quote == str[*i])
	{
		*quote = 0;
		// *have_to_expand = TRUE;
		(*i)++;
		// printf("ICI_1\n");
	}
	if (*quote == 0 && str[*i] == '\"')
	{
		*quote = str[*i];
		*have_to_expand = TRUE;
		(*i)++;
		// printf("ICI_2\n");
	}
	if (*quote == 0 && str[*i] == '\'')
	{
		*quote = str[*i];
		*have_to_expand = FALSE;
		(*i)++;
		// printf("ICI_2\n");
	}
}

static char	*remove_quote(const char *str, t_bool *have_to_expand)
{
	size_t	i;
	size_t	size;
	char	*result;
	char	quote;
	char	*temp;

	result = NULL;
	temp = NULL;
	i = 0;
	quote = 0;
	size = 0;
	while (str[i])
	{
		handle_quote(str, &quote, &i, have_to_expand);
		if (quote == '\"' && str[i] != quote)
		{
			while (str[i] == '"')
				i++;
			size = ft_strlen_charset(&str[i], "");
			temp = ft_strndup(&str[i], size);
			if (!temp)
				return (NULL);
			i += size;
		}
		else if (quote == '\'' && str[i] != quote)
		{
			size = ft_strlen_charset(&str[i], "\'");
			temp = ft_strndup(&str[i], size);
			if (!temp)
				return (NULL);
			i += size;
			// printf("temp : %s\n", temp);
		}
		else
		{
			if (str[i] == '$')
			{
				size = 1;
				i++;
			}
			size += ft_strlen_charset(&str[i], "\'\"$");
			printf("SIZE : %zu\n", size);
			temp = ft_strndup(&str[i], size);
			if (!temp)
				return (NULL);
			i += size;
			// printf("temp : %s\n", temp);
		}
		if (temp)
		{
			result = fill_result(result, temp);
			if (!result)
				return (NULL);
		}
	}
	// printf("result : %s\n", result);
	return (result);
}

static char *expand_string(char *str)
{
	size_t	i;
	size_t	size;
	char	*result;
	char	*temp;

	result = NULL;
	temp = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			size = ft_strlen_charset(&str[i], "$\'\"");
			temp = handle_expand(&str[i], size);
			i += size;
		}
		else
		{
			size = ft_strlen_charset(&str[i], "$");
			temp = ft_strndup(&str[i], size);
			if (!temp)
				return (NULL);
			i += size;
		}
		result = fill_result(result, temp);
	}
	return (result);
}

static char *clean_string(const char *str)
{
	t_bool	have_to_expand;
	char	*result;
	char	*str_without_quote;

	have_to_expand = TRUE;
	result = NULL;
	str_without_quote = remove_quote(str, &have_to_expand);
	if (!str_without_quote)
		return (NULL);
	// if (have_to_expand == FALSE)
	// 	printf("jes uis une banane\n");
	if (have_to_expand == TRUE)
	{
		// printf("Here inside expand\n");
		result = expand_string(str_without_quote);
		if (!result)
			return (NULL);
		// printf("Inside clean_string result : %s\n", result);
	}
	else
		return (str_without_quote);
	return (result);
}

char	*parsing_minishell(const char *str)
{
	char	*result;

	result = clean_string(str);
	if (!result)
		return (NULL);
	return (result);
}
