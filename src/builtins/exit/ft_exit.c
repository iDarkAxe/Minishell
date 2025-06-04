/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:58:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/04 19:36:52 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "garbage.h"
#include "builtins.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

int			ft_exit(t_data *data, char **array);
static int	verif_args(char **array);
static int	ft_strtoull(char *str);
static void	ft_strtoull_utils(char **nptr, short int *minus_sign);
void		check_args_exit(t_data *data, char **array);

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

	check_args_exit(data, array);
	if (FOLLOW_ZSH == 1 || array[1] != NULL)
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	value = verif_args(array);
	if (value == -1)
		return (1);
	if (value == 0)
		value = ft_strtoull(array[0]);
	free_garbage(&data->garbage);
	print_exit(value);
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
		if (ft_isdigit(array[0][count]) != 1 && array[0][count] != '-')
		{
			ft_dprintf(2, "minishell: exit: ");
			ft_dprintf(2, array[0]);
			ft_dprintf(2, ": numeric argument required\n");
			return (2);
		}
		count++;
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
	short int	minus_sign;

	number = 0;
	minus_sign = 0;
	while (*nptr != '\0' && (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
			|| *nptr == '\r' || *nptr == '\v' || *nptr == '\f'))
		nptr++;
	ft_strtoull_utils(&nptr, &minus_sign);
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
	if (minus_sign == -1)
		return ((int)-number);
	return ((int)number);
}

static void	ft_strtoull_utils(char **nptr, short int *minus_sign)
{
	if (**nptr == '-' || **nptr == '+')
	{
		if (**nptr == '-')
			*minus_sign = -1;
		(*nptr)++;
	}
}

void	print_exit(int value)
{
	if (isatty(STDIN_FILENO) == 0)
		return ;
	if (value != 0)
		ft_dprintf(2, "exit\n");
	else
		ft_dprintf(1, "exit\n");
}
