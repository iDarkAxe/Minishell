/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:21:20 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/06 19:27:10 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"

char	*search_env_str(t_garbage *garbage, t_env_vars *env, const char *var,
		size_t size)
{
	char	*str;
	t_var	*head;

	head = env->head_var;
	str = NULL;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, var, size) == 0
			&& ft_strlen(head->value) == size)
		{
			str = create_str_with_params(garbage, head->head_params);
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

t_bool	is_expandable(const char *s, char quote)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] != '$')
		return (FALSE);
	i++;
	if (ft_isalpha(s[i]) == 1 || s[i] == '?' || s[i] == '\'' || s[i] == '"')
	{
		if (quote == '0' || quote == '"')
			return (TRUE);
	}
	printf("\n");
	return (FALSE);
}
