/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:58:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/22 16:48:09 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include <stdlib.h>
#include "minishell.h"

int			ft_exit(char **array);
static int	verif_args(char **array);
static int	ft_strtoull(char *str);

// TODO AJOUTER LE RETOUR ($?) s'il y a trop d'arguments

/**
 * @brief Function to exit the program
 * 
 * @param array argument of the exit function
 * @return int value if argument invalid
 */
int	ft_exit(char **array)
{
	int	value;

	if (array == NULL || array[0] == NULL)
	{
		free_garbage();
		exit(0);
	}
	if (array[1] != NULL)
	{
		print_fd(2, "minishell: exit: too many arguments\n");
		return (-1);
	}
	value = verif_args(array);
	if (value == -1)
		return (1);
	if (value == 0)
		value = ft_strtoull(array[0]);
	free_garbage();
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
			print_fd(2, "minishell: exit: too many arguments\n");
			return (-1);
		}
		if (ft_isdigit(array[0][count++]) != 1)
		{
			print_fd(2, "minishell: exit: ");
			print_fd(2, array[0]);
			print_fd(2, ": numeric argument required\n");
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
 * @return int 
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
			print_fd(2, "minishell: exit: ");
			print_fd(2, nptr);
			print_fd(2, ": numeric argument required\n");
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
// 	if (ft_exit((char *[]){"10", NULL}) != 0)
// 		printf("L'exit est annulé  car l\'input est invalide\n");
// 	free_garbage();
// }
