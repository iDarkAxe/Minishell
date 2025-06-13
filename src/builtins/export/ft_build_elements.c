/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:42:16 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 16:11:30 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

/**
 * @brief build_element_1 create the second array with str  
 * @param str string to copy, 
 * @param i to track the position inside str, 
 * @param j track the position inside the double array 
 */
static void	build_element_1(char **elements, char *str, size_t j, size_t i)
{
	size_t	size_1;

	if (!elements || !str)
		return ;
	size_1 = ft_strlen(&str[i + 1]);
	elements[1] = malloc(sizeof(char) * size_1 + 1);
	if (!elements[0])
	{
		free(elements[0]);
		free(elements);
		elements = NULL;
		return ;
	}
	while (str[++i])
	{
		elements[1][j] = str[i];
		j++;
	}
	elements[1][j] = '\0';
	elements[2] = NULL;
	if (elements[1][0] == '\0')
	{
		free(elements[1]);
		elements[1] = NULL;
	}
}

/**
 * @brief build_element_0 create the firt array with str  
 * @param str string to copy, 
 * @param i to track the position inside str, 
 */
static void	build_element_0(char **elements, char *str, size_t size, size_t *i)
{
	if (!elements || !str)
		return ;
	elements[0] = malloc(sizeof(char) * size + 1);
	if (!elements[0])
	{
		free(elements);
		elements = NULL;
		return ;
	}
	elements[1] = NULL;
	while (str[*i] && str[*i] != '=')
	{
		elements[0][*i] = str[*i];
		(*i)++;
	}
	elements[0][*i] = '\0';
}

/**
 * @brief build_elements split str on the equal 
 * and put the value in two differents strings  
 * @param str string to split 
 * @return an array of strings 
 */
char	**build_elements(char *str)
{
	char	**elements;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	elements = malloc(sizeof(char *) * 3);
	if (!elements)
		return (NULL);
	size = ft_strlen_choose_c(str, '=');
	i = 0;
	j = 0;
	build_element_0(elements, str, size, &i);
	if (!elements)
		return (NULL);
	if (str[i] == '=' && str[i + 1] != '\0')
		build_element_1(elements, str, j, i);
	return (elements);
}
