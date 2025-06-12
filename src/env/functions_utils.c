/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42lyon.fr>        +  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:02:53 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/11 14:12:26 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int		ft_strcmp(const char *s1, const char *s2);
t_bool	detect_equal(char *str);

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
	while (str && *str)
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

	i = 0;
	while (str && str[i] && str[i] != c)
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
