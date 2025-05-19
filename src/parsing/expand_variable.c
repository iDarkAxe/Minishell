/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:05:11 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/18 09:46:40 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "garbage.h"
#include "libft.h"
#include "parsing.h"

char	*search_env_str(const char *var, size_t size)
{
	char		*str;
	t_var		*head;
	t_env_vars	*env;

	env = get_env();
	head = env->head_var;
	str = NULL;
	while (head != NULL)
	{
		if (ft_strncmp(head->value, var, size) == 0)
		{
			str = create_str_with_params(head->head_params);
			if (!str)
				return (NULL);
		}
		head = head->next;
	}
	if (head == NULL && str == NULL)
		str = ft_strdup(NULL);
	return (str);
}

static void	free_temps(char *temp, char *temp_1)
{
	free(temp_1);
	free(temp);
}

char	*handle_expand(const char *str, size_t size)
{
	char	*result;

	result = search_env_str(str, size);
	if (!result)
		return (NULL);
	return (result);
}

void	handle_normal_characters(const char *str, char **string_to_stack,
		size_t size, size_t i)
{
	char	*temp;
	char	*temp_1;

	temp = NULL;
	temp_1 = ft_strndup(&str[i], size);
	if (!temp_1)
		return ;
	/*printf("NORMAL : TEMP_1 : %s\n", temp_1);*/
	if (*string_to_stack)
	{
		temp = ft_strdup(*string_to_stack);
		if (!temp)
			return ;
	}
	/*printf("NORMAL : TEMP : %s\n", temp);*/
	if (*string_to_stack)
		free(*string_to_stack);
	if (temp)
		*string_to_stack = ft_strjoin(temp, temp_1);
	else
		*string_to_stack = ft_strdup(temp_1);
	if (!*string_to_stack)
		return ;
	/*printf("NORMAL : STRING TO : %s\n", *string_to_stack);*/
	free_temps(temp, temp_1);
}

/*char	*expand_variables_line(char *str)*/
/*{*/
/*	char	*string_to_stack;*/
/*	size_t	size;*/
/*	size_t	i;*/
/**/
/*	string_to_stack = NULL;*/
/*	size = 0;*/
/*	i = 0;*/
/*	while (str && str[i])*/
/*	{*/
/*		if (str[i] == '$')*/
/*		{*/
/*			i++;*/
/*			size = ft_strlen_charset(&str[i], "$ ");*/
/*			handle_expand(str, &string_to_stack, size, i);*/
/*			i += size;*/
/*		}*/
/*		else*/
/*		{*/
/*			size = ft_strlen_choose_c(&str[i], '$');*/
/*			handle_normal_characters(str, &string_to_stack, size, i);*/
/*			i += size;*/
/*			continue ;*/
/*		}*/
/*		i++;*/
/*	}*/
/*	add_to_garbage(string_to_stack);*/
/*	return (string_to_stack);*/
/*}*/
