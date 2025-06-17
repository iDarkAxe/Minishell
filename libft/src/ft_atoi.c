/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:34:53 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 13:06:49 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr);

/**
 * @brief Convert string to int, and handle number
 *
 * @param nptr string to convert
 * @return int number
 */
int	ft_atoi(const char *nptr)
{
	long		number;
	long		overflow_tester;
	short int	minus_sign;

	number = 0;
	minus_sign = 0;
	while (*nptr != '\0' && (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
			|| *nptr == '\r' || *nptr == '\v' || *nptr == '\f'))
		nptr++;
	if (*nptr != '\0' && ((*nptr == '-') || (*nptr == '+')))
	{
		if (*nptr == '-')
			minus_sign = -1;
		nptr++;
	}
	while (*nptr != '\0' && *nptr >= '0' && *nptr <= '9')
	{
		overflow_tester = number;
		number = number * 10 + *nptr++ - '0';
		if (overflow_tester > number)
			return (-(!minus_sign));
	}
	if (minus_sign == -1)
		return ((int)-number);
	return ((int)number);
}

// #include <stdlib.h>
// #include "libft.h"
// int main(int argc, char **argv)
// {
// 	char *nbr;
// 	if (argc >= 2)
// 	{
//		ft_putendl_fd(argv[1], 1);
// 		ft_putstr_fd("Resultat attendu : ", 1);
// 		ft_putnbr_fd(atoi(argv[1]), 1);
// 		ft_putendl_fd("", 1);
// 		ft_putstr_fd("Resultat test   : ", 1);
// 		ft_putnbr_fd(ft_atoi(argv[1]), 1);
// 		ft_putendl_fd("", 1);
// 		ft_putendl_fd("     -----     ", 1);
// 	}
// 	else
// 	{
// 		nbr = " 22246635";
// 		ft_putendl_fd(nbr, 1);
// 		ft_putstr_fd("Resultat attendu : ", 1);
// 		ft_putnbr_fd(atoi(nbr), 1);
// 		ft_putendl_fd("", 1);
// 		ft_putstr_fd("Resultat test   : ", 1);
// 		ft_putnbr_fd(ft_atoi(nbr), 1);
// 		ft_putendl_fd("", 1);
// 		ft_putendl_fd("     -----     ", 1);
// 		nbr = " 195498494949809846841";
// 		ft_putendl_fd(nbr, 1);
// 		ft_putstr_fd("Resultat attendu : ", 1);
// 		ft_putnbr_fd(atoi(nbr), 1);
// 		ft_putendl_fd("", 1);
// 		ft_putstr_fd("Resultat test   : ", 1);
// 		ft_putnbr_fd(ft_atoi(nbr), 1);
// 		ft_putendl_fd("", 1);
// 		ft_putendl_fd("     -----     ", 1);
// 		nbr = " -195498494949809846841";
// 		ft_putendl_fd(nbr, 1);
// 		ft_putstr_fd("Resultat attendu : ", 1);
// 		ft_putnbr_fd(atoi(nbr), 1);
// 		ft_putendl_fd("", 1);
// 		ft_putstr_fd("Resultat test   : ", 1);
// 		ft_putnbr_fd(ft_atoi(nbr), 1);
// 		ft_putendl_fd("", 1);
// 		ft_putendl_fd("     -----     ", 1);
// 	}
// }
