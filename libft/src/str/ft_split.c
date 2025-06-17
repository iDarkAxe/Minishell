/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:45:58 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/15 11:41:06 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void			ft_free_malloc(char **ptr_ptr, size_t count);
static const char	*ft_strchr_end(const char *string, int searched_char);
static size_t		str_count_char(char const *s, char c);

/**
 * @brief Allocates with a malloc and returns an array of strings
 * obtained by separating ’s’ using the character ’c’,
 * used as a delimiter. The array must be terminated by NULL
 *
 * @param s string to print
 * @param c char used as a delimiter
 * @return char** array of strings
 */
char	**ft_split(char const *s, char c)
{
	char	**ptr_ptr;
	size_t	count;
	size_t	nbr_cuts;

	count = 0;
	nbr_cuts = str_count_char(s, c);
	ptr_ptr = malloc(sizeof(char *) * (nbr_cuts + 1));
	if (ptr_ptr == NULL)
		return (NULL);
	while (nbr_cuts-- > 0)
	{
		while (*s == c && *s != '\0')
			s++;
		ptr_ptr[count] = ft_substr(s, 0, (size_t)(ft_strchr_end(s, c) - s));
		if (ptr_ptr[count++] == NULL)
		{
			ft_free_malloc(ptr_ptr, count - 1);
			return (NULL);
		}
		s += ft_strchr_end(s, c) - s;
	}
	ptr_ptr[count] = NULL;
	return (ptr_ptr);
}

/**
 * @brief Work exactly like strchr, but return end of string
 * if searched_char not found
 *
 * @param string string to search in
 * @param searched_char char to search
 * @return char* pointer to the first occurence of searched_char
 */
static const char	*ft_strchr_end(const char *string, int searched_char)
{
	char	*pointer;

	pointer = ft_strchr(string, searched_char);
	if (pointer == NULL)
		return (&string[ft_strlen(string)]);
	return (pointer);
}

/**
 * @brief Free mallocs
 *
 * @param ptr_ptr pointer to pointer
 * @param count number of pointers
 */
static void	ft_free_malloc(char **ptr_ptr, size_t count)
{
	while (count > 0)
		free(ptr_ptr[--count]);
	free(ptr_ptr);
}

/**
 * @brief Count occurrence of c in string s
 *
 * @param s string to search in
 * @param c char to search
 * @return size_t number of occurence
 */
static size_t	str_count_char(char const *s, char c)
{
	size_t			count;
	unsigned char	in_substring;

	count = 0;
	in_substring = 0;
	while (*s != '\0')
	{
		if (*s == c)
			in_substring = 0;
		else if (!in_substring)
		{
			in_substring = 1;
			count++;
		}
		s++;
	}
	return (count);
}

// int main(void)
// {
// 	char **ptr = ft_split("lorem ipsum spendisse\n", ' ');
// 	char **tab = ft_split("tripouille", 0);
// 	size_t index = 0;

// 	// while (ptr[index] != NULL)
// 	// {
// 	// 	ft_putendl_fd(ptr[index], 1);
// 	// 	index++;
// 	// }
// 	while (ptr[index] != NULL)
// 	{
// 		ft_putendl_fd(tab[index], 1);
// 		index++;
// 	}
// }
