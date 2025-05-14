/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:05:11 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/14 11:47:09 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "builtins.h"
#include "libft.h"
#include "parsing.h"

char	*search_env_str(char *var, size_t size)
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

static void handle_expand(char *str, char **string_to_stack, size_t size, size_t i)
{
	char	*temp;
	char	*temp_1;

	temp_1 = search_env_str(&str[i], size);
	if (!temp_1)
		return ;
	if (*string_to_stack == NULL)
	{
		*string_to_stack = ft_strdup(temp_1);
		if (!*string_to_stack)
			return ;
		free(temp_1);
	}
	else
	{
		temp = ft_strdup(*string_to_stack);
		if (!temp)
			return ;
		free(*string_to_stack);
		*string_to_stack = ft_strjoin(temp, temp_1);
		if (!*string_to_stack)
			return ;
		free_temps(temp, temp_1);
	}
	return ;
}

static void handle_normal_characters(char *str, char **string_to_stack, size_t size, size_t i)
{
	char	*temp;
	char	*temp_1;

	temp_1 = ft_strndup(&str[i], size);
	if (!temp_1)
		return ;
	temp = ft_strdup(*string_to_stack);
	if (!temp)
		return ;
	free(*string_to_stack);
	*string_to_stack = ft_strjoin(temp, temp_1);
	if (!*string_to_stack)
		return ;
	free_temps(temp, temp_1);
}

char	*expand_variables_line(char *str)
{
	char		*string_to_stack;
	size_t		size;
	size_t		i;

	string_to_stack = NULL;
	size = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			i++;
			size = ft_strlen_charset(&str[i], "$ ");
			handle_expand(str, &string_to_stack, size ,i);
		}
		else
		{
			size = ft_strlen_choose_c(&str[i], '$');
			handle_normal_characters(str, &string_to_stack, size, i);
			i += size;
			continue ;
		}
		i++;
	}
	add_to_garbage(string_to_stack);
	return (string_to_stack);
}
