/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>        +  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:19:42 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/11 13:57:02 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_bool			is_charset(char c, char *charset);
char			**ft_split_charset(const char *s, char *charset);

t_bool	is_charset(char c, char *charset)
{
	size_t	i;

	i = 0;
	if (!charset)
		return (FALSE);
	while (charset[i])
	{
		if (charset[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static size_t	count_words(char const *s, char *charset)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s && s[i] != '\0')
	{
		if (is_charset(s[i], charset) == FALSE && (is_charset(s[i + 1],
					charset) == TRUE || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	**ft_free(char **strs, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j + 1)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static char	*ft_strdupp(const char *s, char *charset, size_t *i)
{
	char	*dest;
	size_t	len;
	size_t	j;

	len = 0;
	j = 0;
	while (is_charset(s[*i], charset) == FALSE && s[*i] != '\0')
	{
		len++;
		(*i)++;
	}
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (dest);
	*i -= len;
	while (is_charset(s[*i], charset) == FALSE && s[*i] != '\0')
	{
		dest[j] = s[*i];
		(*i)++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	**ft_split_charset(const char *s, char *charset)
{
	char	**final_array;
	size_t	size;
	size_t	i;
	size_t	j;

	size = count_words(s, charset);
	i = 0;
	j = 0;
	final_array = ft_calloc(size + 1, sizeof(char *));
	if (!final_array)
		return (final_array);
	while (j < size)
	{
		while (is_charset(s[i], charset) == TRUE)
			i++;
		final_array[j] = ft_strdupp(s, charset, &i);
		if (!final_array[j])
			return (ft_free(final_array, j));
		while (is_charset(s[i], charset) == TRUE && s[i] != '\0')
			i++;
		j++;
	}
	return (final_array);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char *str = "fdasfasfa | fdasfasfa < fdasfasfas";
// 	char **new_str;
//
// 	new_str = ft_split_charset(str, "|%><");
// 	for (int i = 0; new_str[i] != NULL; i++)
// 	{
// 		printf("%s", new_str[i]);
// 		free(new_str[i]);
// 	}
// 	free(new_str);
// 	return (0);
// }
