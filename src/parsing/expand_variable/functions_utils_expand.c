/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:21:20 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/11 14:51:19 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "libft.h"
#include "data_structure.h"
#include "parsing.h"

char	*search_env_str(t_data *data, const char *var, size_t size)
{
	char	*str;
	t_var	*head;

	head = data->env.head_var;
	str = NULL;
	if (*var == '?')
	{
		str = ft_itoa(data->ret);
		return (str);
	}
	while (head != NULL)
	{
		if (ft_strncmp(head->value, var, size) == 0
			&& ft_strlen(head->value) == size)
		{
			str = create_str_with_params(&data->garbage, head->head_params);
			if (!str)
				return (NULL);
			return (str);
		}
		head = head->next;
	}
	if (head == NULL && str == NULL)
		str = ft_strdup(NULL);
	return (str);
}

static void	setup_quote(char *str, char *quote, t_bool *is_expandable)
{
	if (*quote == '0' && *str == '"')
	{
		*quote = *str;
		*is_expandable = TRUE;
	}
	else if (*quote == '0' && *str == '\'')
	{
		*quote = *str;
		*is_expandable = FALSE;
	}
	else if (*quote == *str)
	{
		*quote = '0';
		*is_expandable = TRUE;
	}
	str++;
	if (ft_isalnum(*str) == 1 || *str == '$' || *str == '?')
		return ;
	setup_quote(str, quote, is_expandable);
}

t_bool	is_expandable(char *s)
{
	size_t	i;
	char	quote;
	t_bool	is_expandable;

	i = 0;
	quote = '0';
	is_expandable = TRUE;
	if (!s)
		return (FALSE);
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] != '$')
		return (FALSE);
	else if (s[i] == '$' && (s[i + 1] == '\'' || s[i + 1] == '"'))
		return (TRUE);
	i++;
	if (ft_isalpha(s[i]) == 1 || s[i] == '?' || s[i] == '\'' || s[i] == '"')
	{
		setup_quote(s, &quote, &is_expandable);
		if (is_expandable == TRUE)
			return (TRUE);
	}
	return (FALSE);
}
