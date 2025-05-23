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
#include "env.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "parsing.h"

size_t		count_without_quote(const char *str);

/**
 * @brief Prototype for parsing
 *
 * @param line line to parse
 * @return char**
 */
char	**parse_line(char *line)
{
	char	**tokens;

	line = clean_string(line);
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

char	*fill_result(char *result, char *temp)
{
	char	*temp_result;

	temp_result = NULL;
	if (!result)
	{
		result = ft_strdup(temp);
		if (!result)
			return (NULL);
	}
	else if (result && temp)
	{
		temp_result = ft_strdup(result);
		if (!temp_result)
			return (NULL);
		free(result);
		result = ft_strjoin(temp_result, temp);
		if (!result)
			return (NULL);
		free(temp_result);
	}
	return (result);
}

// void	handle_quote(const char *str, char *quote, size_t *i, t_bool *expand)
// {
// 	if (*quote == str[*i])
// 	{
// 		*quote = 0;
// 		(*i)++;
// 	}
// 	else if (*quote == 0 && str[*i] == '\"')
// 	{
// 		*quote = str[*i];
// 		*expand = TRUE;
// 		(*i)++;
// 	}
// 	else if (*quote == 0 && str[*i] == '\'')
// 	{
// 		*quote = str[*i];
// 		*expand = FALSE;
// 		(*i)++;
// 	}
// 	while (str[*i] && str[*i] == *quote)
// 	{
// 		if (*quote == str[*i])
// 		{
// 			*quote = 0;
// 			*expand = TRUE;
// 		}
// 		else
// 		{
// 			*quote = str[*i];
// 			if (*quote == '\'')
// 				*expand = FALSE;
// 		}
// 		(*i)++;
// 	}
// }

void	handle_quote(const char *str, char *quote, size_t *i, t_bool *expand)
{
	if (*quote == 0 && (str[*i] == '\'' || str[*i] == '"'))
	{
		*quote = str[*i];
		if (str[*i] == '"')
			*expand = TRUE;
		else
			*expand = FALSE;
		(*i)++;
	}
	else if (*quote != 0 && str[*i] == *quote)
	{
		*quote = 0;
		// *expand = TRUE;
		(*i)++;
	}
}

static char	*remove_quote(const char *str, t_bool *expand)
{

	size_t	i;
	size_t	size;
	char	quote;
	char	*result;
	char	*temp;

	result = NULL;
	temp = NULL;
	i = 0;
	quote = 0;
	size = 0;
	while (str[i])
	{
		handle_quote(str, &quote, &i, expand);
		if (str[i] == '\0')
			break ;
		// if ((str[i] == '\'' || str[i] == '"') && str[i] == quote)
		// {
		// 	printf("je suis ici");
		// 	continue ;
		// }
		if (str[i] != quote)
		{
			if (quote == 0)
			{
				printf("HERE\n");
				size = ft_strlen_charset(str, "\"\'$");
			}
			else
				size = ft_strlen_choose_c(&str[i], quote);
			printf("size: %zu\n", size);
			temp = ft_strndup(&str[i], size);
			if (!temp)
				return (NULL);
			i += size;
		}
		if (temp)
		{
			result = fill_result(result, temp);
			if (!result)
				return (NULL);
			free(temp);
		}
	}
	return (result);
}

char	*clean_string(const char *str)
{
	t_bool	expand;
	char	*result;
	char	*str_without_quote;

	expand = TRUE;
	result = NULL;
	str_without_quote = remove_quote(str, &expand);
	if (!str_without_quote)
		return (NULL);
	if (expand == TRUE)

	{
		result = handle_expand(str_without_quote);
		if (!result)
			return (NULL);
		add_to_garbage(result);
	}
	else
		return (str_without_quote);
	add_to_garbage(str_without_quote);
	return (result);
}
