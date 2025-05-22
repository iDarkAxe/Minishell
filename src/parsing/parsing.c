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

size_t	count_without_quote(const char *str)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (str && str[i])
	{
		if (quote != 0 && str[i] == quote)
			quote = 0;
		else if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else
			count++;
		i++;
	}
	return (count);
}

static t_bool	has_unclosed_quote(const char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (str && str[i])
	{
		if (quote != 0 && str[i] == quote)
			quote = 0;
		else if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		i++;
	}
	if (quote == 0)
		return (FALSE);
	return (TRUE);
}

// static char	*remove_quote(const char *str, char *new_str)
// {
// 	char	quote;
// 	size_t	i;
// 	size_t	j;
//
// 	i = 0;
// 	j = 0;
// 	quote = 0;
// 	while (str && str[i])
// 	{
// 		if (quote != 0 && str[i] == quote)
// 			quote = 0;
// 		else if (quote == 0 && (str[i] == '\"' || str[i] == '\''))
// 			quote = str[i];
// 		else
// 			new_str[j++] = str[i];
// 		i++;
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);
// }
//
static char *close_quote(const char *str, char *new_str, t_bool *have_to_expand)
{
	char	quote;
	char	*temp;
	char	*temp_new_str;
	size_t	i;
	size_t	size;

	i = 0;
	quote = 0;
	temp = NULL;
	temp_new_str = NULL;
	while (str && str[i])
	{
		if (quote == str[i])
			quote = 0;
		else if (quote == 0 && str[i] == '\'')
		{
			*have_to_expand = FALSE;
			quote = str[i];
			i++;
		}
		else if (quote == 0 && str[i] == '"')
		{
			*have_to_expand = TRUE;
			quote = str[i];
			i++;
		}
		if (str[i] == '$' && *have_to_expand == TRUE)
		{
			i++;
			size = ft_strlen_charset(&str[i], "$ \"");
			temp = handle_expand(&str[i], size);
			i += size;
		}
		else
		{
			size = ft_strlen_charset(&str[i] ,"'\"");
			temp = ft_strndup(&str[i], size);
			if (!temp)
				return (NULL);
			i += size;
		}
		if (new_str == NULL && temp)
		{
			new_str = ft_strdup(temp);
			if (!new_str)
				return (NULL);
			free(temp);
			temp = NULL;

		}
		else if (new_str != NULL && temp)
		{
			temp_new_str = ft_strdup(new_str);
			if (!temp_new_str)
				return (NULL);
			free(new_str);
			new_str = ft_strjoin(temp_new_str, temp);
			if (!new_str)
				return (NULL);
			free(temp_new_str);
			free(temp);
		}
	}
	add_to_garbage(new_str);
	return (new_str);
}

char	*parsing_minishell(const char *str)
{
	char	*new_str;
	t_bool	have_to_expand;
	char	*result;

	if (!str || has_unclosed_quote(str) == TRUE)
		return (NULL);
	have_to_expand = TRUE;
	new_str = NULL;
	result = new_str;
	return (result);
}
