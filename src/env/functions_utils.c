/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:02:53 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/16 17:54:25 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int		ft_strcmp(const char *s1, const char *s2);
t_bool	detect_equal(char *str);
t_bool	detect_dollar_str(char *str);
size_t	ft_strlen_choose_c(const char *str, char c);
t_bool	ft_is_special_character(char c);

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

t_bool	detect_dollar_str(char *str)
{
	if (!str)
		return (FALSE);
	while (*str)
	{
		if (*str == '$')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

size_t	ft_strlen_choose_c(const char *str, char c)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

t_bool	ft_is_special_character(char c)
{
	if ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c >= '['
			&& c <= '`') || (c >= '{' && c <= '~'))
		return (TRUE);
	return (FALSE);
}
