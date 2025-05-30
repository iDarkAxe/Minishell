/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:58:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/30 11:20:40 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

int			ft_exit(t_data *data, char **array);
void		ft_exit_int(t_garbage *garbage,
				int value) __attribute__((noreturn));
void		ft_exit_int_np(t_garbage *garbage,
				int value) __attribute__((noreturn));
static int	verif_args(char **array);
static int	ft_strtoull(char *str);

/**
 * @brief Short ft_exit that uses only int
 * noreturn attribute is to prevent -Wmissing-noreturn flag
 * from flag -Weverything of debug-cc
 *
 * @param garbage garbage structure
 * @param value value
 */

void	ft_exit_int(t_garbage *garbage, int value)
{
	free_garbage(garbage);
	ft_printf("exit\n");
	exit((unsigned char)value);
}

/**
 * @brief Short ft_exit that uses only int but don't say it's name
 *
 * @param garbage garbage structure
 * @param value value
 */
void	ft_exit_int_np(t_garbage *garbage, int value)
{
	free_garbage(garbage);
	exit((unsigned char)value);
}

/* Zsh exit if there is more than 1 argument, bash don't.
SET FOLLOW_ZSH to 1 to follow zsh behavior. */

/**
 * @brief Function to exit the program
 *
 * @param data data structure
 * @param array argument of the exit function
 * @return int value if argument invalid
 */
int	ft_exit(t_data *data, char **array)
{
	int	value;

	if (array == NULL || array[0] == NULL)
	{
		value = data->ret;
		free_garbage(&data->garbage);
		ft_dprintf(1, "exit\n");
		exit(value);
	}
	if (FOLLOW_ZSH == 1 && array[1] != NULL)
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		return (-1);
	}
	value = verif_args(array);
	if (value == -1)
		return (1);
	if (value == 0)
		value = ft_strtoull(array[0]);
	free_garbage(&data->garbage);
	ft_dprintf(1, "exit\n");
	exit((unsigned char)value);
}

/**
 * @brief Verify that the argument of exit are acceptable
 *
 * @param array argument of the exit function
 * @return int negative if invalid, otherwise it's valid
 */
static int	verif_args(char **array)
{
	size_t	count;

	count = 0;
	while (array != NULL && array[0] != NULL && array[0][count] != '\0')
	{
		if (ft_isspace(array[0][count]) != 0)
		{
			ft_dprintf(2, "minishell: exit: too many arguments\n");
			return (-1);
		}
		if (ft_isdigit(array[0][count++]) != 1)
		{
			ft_dprintf(2, "minishell: exit: ");
			ft_dprintf(2, array[0]);
			ft_dprintf(2, ": numeric argument required\n");
			return (2);
		}
	}
	return (0);
}

/**
 * @brief Specific strtoll for exit
 * Returns 2 if long long max value is exceeded
 *
 * @param nptr string to search numbers
 * @return int cast of a long long into an int, 2 if overflow long long type
 */
static int	ft_strtoull(char *nptr)
{
	long long	number;
	long long	overflow_tester;

	number = 0;
	while (*nptr != '\0' && (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
			|| *nptr == '\r' || *nptr == '\v' || *nptr == '\f'))
		nptr++;
	while (*nptr != '\0' && *nptr >= '0' && *nptr <= '9')
	{
		overflow_tester = number;
		number = number * 10 + *nptr++ - '0';
		if (overflow_tester > number)
		{
			ft_dprintf(2, "minishell: exit: ");
			ft_dprintf(2, nptr);
			ft_dprintf(2, ": numeric argument required\n");
			return (2);
		}
	}
	return ((int)number);
}

// #include <stdio.h>
// #include <stdlib.h>
// /*
// Génère des allocations qui sont attrapées par le garbage collector,
// il ne devrait pas y a voir de leak.
// */

// int main(void)
// {
// 	char	*str;
// 	size_t	count;

// 	count = 0;
// 	while (count < 10)
// 	{
// 		str = ft_strdup("tsets");
// 		add_to_garbage(str);
// 		count++;
// 	}
// 	if (ft_exit_int(10) != 0)
// 		printf("L'exit est annulé  car l\'input est invalide\n");
// 	free_garbage(garbage);
// }
