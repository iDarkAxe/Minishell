/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:58:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/22 16:42:19 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include <stdlib.h>
#include "minishell.h"

int			ft_exit(char *str);
static int	verif_args(char *str);

// TODO AJOUTER LE RETOUR ($?) s'il y a trop d'arguments

/**
 * @brief Function to exit the program
 * 
 * @param str argument of the exit function
 * @return int value if argument invalid
 */
int	ft_exit(char *str)
{
	int	value;

	if (str == NULL)
	{
		free_garbage();
		exit(0);
	}
	value = verif_args(str);
	if (value == -1)
		return (1);
	if (value != 0)
		value = ft_atoi(str);
	free_garbage();
	exit(value);
}

/**
 * @brief Verify that the argument of exit are acceptable
 *
 * @param str argument of the exit function
 * @return int negative if invalid, otherwise it's valid
 */
static int	verif_args(char *str)
{
	size_t	count;

	count = 0;
	while (str != NULL && str[count] != '\0')
	{
		if (ft_isspace(str[count]) != 0)
		{
			print_fd(2, "minishell: exit: too many arguments\n");
			return (-1);
		}
		if (ft_isdigit(str[count]) == 0)
		{
			print_fd(2, "minishell: exit: ");
			print_fd(2, str);
			print_fd(2, ": numeric argument required\n");
			return (2);
		}
		count++;
	}
	return (0);
}

// #include <stdio.h>

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
// 	if (ft_exit("10 10") != 0)
// 		printf("L'exit est annulé  car l\'input est invalide\n");
// 	free_garbage();
// }
