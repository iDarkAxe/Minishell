/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:31:24 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/13 14:53:47 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "data_structure.h"

/**
 * @brief ft_count_var count the number of t_var inside env
 *
 * @param data allow to get env 
 * @return size_t
 */
static size_t	ft_count_var(t_data *data)
{
	size_t	count;
	t_var	*temp;

	count = 0;
	temp = data->env.head_var;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

/**
 * @brief count_char_of_var count all the characters of a var
 *
 * @param var to count, nbr_param reference of a total param number of a var 
 * @return size_t 
 */
static size_t	count_char_of_var(t_var *var, size_t *nbr_param)
{
	t_params	*temp;
	size_t		count;
	size_t		i;

	i = 0;
	count = 1;
	temp = var->head_params;
	while (var && var->value[i])
	{
		count++;
		i++;
	}
	i = 0;
	while (temp != NULL)
	{
		while (temp && temp->value[i])
		{
			count++;
			i++;
		}
		temp = temp->next;
		(*nbr_param)++;
		i = 0;
	}
	return (count);
}

/**
 * @brief params_to_str paramns to transform into a string
 *
 * @param var allow to get the params inside 
 */
static void	params_to_str(char **str, t_var *var, size_t i_str)
{
	size_t		i;
	t_params	*temp;

	temp = var->head_params;
	if (!temp)
		return ;
	while (temp != NULL)
	{
		i = 0;
		while (temp && temp->value[i])
		{
			(*str)[i_str] = temp->value[i];
			i++;
			i_str++;
		}
		if (temp->next != NULL)
			(*str)[i_str++] = ':';
		temp = temp->next;
	}
	(*str)[i_str] = '\0';
}

/**
 * @brief var_to_str transform t_var to str
 *
 * @param var t_var to transform into string 
 * @return char *
 */
static char	*var_to_str(t_var *var)
{
	char	*str;
	size_t	i;
	size_t	i_str;
	size_t	count;
	size_t	nbr_param;

	if (!var)
		return (NULL);
	nbr_param = 0;
	count = count_char_of_var(var, &nbr_param) + 1;
	str = malloc(sizeof(char) * (count + nbr_param + 1));
	if (!str)
		return (NULL);
	ft_bzero(str, sizeof(char) * (count + nbr_param + 1));
	i = 0;
	i_str = 0;
	while (var && var->value[i])
	{
		str[i_str] = var->value[i];
		i++;
		i_str++;
	}
	str[i_str++] = '=';
	params_to_str(&str, var, i_str);
	return (str);
}

/**
 * @brief env_to_array transform env to a array of string
 *
 * @param data structure to get env 
 * @return char **
 */
char	**env_to_array(t_data *data)
{
	size_t	i;
	size_t	size;
	char	**array;
	t_var	*temp;

	i = 0;
	size = ft_count_var(data) + 1;
	temp = data->env.head_var;
	array = malloc_gb(&data->garbage, sizeof(char *) * size);
	while (temp != NULL)
	{
		array[i] = var_to_str(temp);
		if (array[i] != NULL)
			add_to_garbage(&data->garbage, array[i]);
		temp = temp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
