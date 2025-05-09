/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:42:16 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/09 16:42:45 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	build_element_1(char **elements, char *str, size_t j, size_t i)
{
	size_t size_1;

	size_1 = ft_strlen(&str[i + 1]);
	elements[1] = malloc(sizeof(char) * size_1 + 1);
	if (!elements[1])
		return ;
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

static void	build_element_0(char **elements, char *str, size_t size, size_t *i)
{
	elements[0] = malloc(sizeof(char) * size + 1);
	if (!elements[0])
		return ;
	elements[1] = NULL;
	while (str[*i] && str[*i] != '=')
	{
		elements[0][*i] = str[*i];
		(*i)++;
	}
	elements[0][*i] = '\0';
}

char	**build_elements(char *str)
{
	char	**elements;
	size_t	size;
	size_t	i;
	size_t	j;

	elements = malloc(sizeof(char *) * 3);
	if (!elements)
		return (NULL);
	size = ft_strlen_choose_c(str, '=');
	i = 0;
	j = 0;
	build_element_0(elements, str, size, &i);
	if (str[i] == '=')
		build_element_1(elements, str, j, i);
	return (elements);
}
