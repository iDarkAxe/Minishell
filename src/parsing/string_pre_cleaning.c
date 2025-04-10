/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_pre_cleaning.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:58:14 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/08 13:04:59 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

t_bool	detect_pair_quote(const char *str, char quote)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str)
		return (FALSE);
	while (str[i])
	{
		if (str[i] == quote)
			count++;
		i++;
	}
	if (count > 0 && count % 2 == 0)
		return (TRUE);
	return (FALSE);
}

char *string_pre_cleaning(const char *str)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = ft_strtrim(str, " \t\n\r\u00A0\v\f");
	if (!new_str || *new_str == '\0')
		return (NULL);
	if (detect_pair_quote(str, '"') == FALSE && detect_pair_quote(str, '\'') == FALSE)
	{
		free(new_str);
		return (NULL);
	}
	return (new_str);
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	char *test = "    \"     fdsafsfa     \"      ";
// 	char	*new_str;
//
// 	new_str = string_pre_cleaning(test);
// 	printf("%s", new_str);
// 	free(new_str);
// 	// free(test);
// 	return (0);
// }
