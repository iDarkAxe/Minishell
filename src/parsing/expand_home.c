/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:10:42 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/09 16:36:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "garbage.h"
#include "libft.h"
#include "builtins.h"

static void	change_tildes_by_home(char *result, char *home, char *str);
static char	*expand_tildes(char *str);

/**
 * @brief Expands all the tildes found in array with HOME
 * 
 * @param tokens array of strings 
 * @return char** tokens if OK, NULL otherwise
 */
char	**expand_tildes_tokens(char **tokens)
{
	size_t	index;

	if (tokens == NULL || tokens[0] == NULL)
		return (NULL);
	index = 0;
	while (tokens[index] != NULL)
	{
		if (ft_strchr(tokens[index], '~') != NULL)
			tokens[index] = expand_tildes(tokens[index]);
		if (tokens[index] == NULL)
		{
			free_array(tokens);
			ft_exit_int_np(1);
		}
		index++;
	}
	return (tokens);
}

/**
 * @brief Expand the '~' sign in a string
 * 
 * @param str string to modify 
 * @return char* 
 */
static char	*expand_tildes(char *str)
{
	char	*home;
	char	*result;
	size_t	count_tildes;

	if (str == NULL)
		return (NULL);
	home = getenv("HOME");
	if (home == NULL)
		return (ft_strdup_gb(str));
	count_tildes = ft_strlen_char(str, '~');
	result = malloc(ft_strlen(str) + 1 + count_tildes * ft_strlen(home));
	if (result == NULL)
	{
		free_element_gb(str);
		ft_exit((char *[]){"1", NULL});
	}
	add_to_garbage(result);
	change_tildes_by_home(result, home, str);
	free_element_gb(str);
	return (result);
}

/**
 * @brief Change all the tildes by home
 * 
 * @param result resulting string
 * @param home path to HOME
 * @param str input string
 */
static void	change_tildes_by_home(char *result, char *home, char *str)
{
	size_t	len;
	size_t	index;
	size_t	home_len;

	len = 0;
	index = 0;
	if (result == NULL || home == NULL || str == NULL)
		return ;
	home_len = ft_strlen(home);
	while (str[index])
	{
		if (str[index] == '~')
		{
			ft_memcpy(&result[len], home, home_len);
			len += home_len;
			index++;
		}
		else
			result[len++] = str[index++];
	}
	result[len] = '\0';
}
