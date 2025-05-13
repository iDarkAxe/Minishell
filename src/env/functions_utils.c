/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:02:53 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/13 18:03:33 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlen_choose_c(const char *str, char c);
int		ft_strcmp(const char *s1, const char *s2);
t_bool	detect_equal(char *str);

static t_bool	is_charset(const char *charset, char c)
{
	size_t	i;

	i = 0;
	while (charset && charset[i])
	{
		if (charset[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

size_t	ft_strlen_charset(const char *str, const char *charset)
{
	size_t	i;

	i = 0;
	while (str && str[i] && is_charset(charset, str[i]) == FALSE)
		i++;
	return (i);
}

size_t	ft_strlen_choose_c(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

t_bool	detect_equal(char *str)
{
	size_t	i;

	if (!str)
		return (FALSE);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}
