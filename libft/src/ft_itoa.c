/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:27:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 13:27:34 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static unsigned char	count_numbers(int n);

/**
 * @brief Return a string representing the integer 'n' received as argument
 *
 * @param n integer to convert
 * @return char* string representing the integer 'n'
 */
char	*ft_itoa(int n)
{
	unsigned char	nbr_char;
	char			*pointer;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr_char = count_numbers(n);
	pointer = malloc(sizeof(char) * (nbr_char + 1));
	if (pointer == NULL)
		return (NULL);
	pointer[nbr_char--] = '\0';
	if (n < 0)
	{
		pointer[0] = '-';
		n = -n;
	}
	while (n >= 10)
	{
		pointer[nbr_char] = n % 10 + '0';
		n /= 10;
		nbr_char--;
	}
	pointer[nbr_char] = (char) n + (char) '0';
	return (pointer);
}

/**
 * @brief Count the number of digits in the integer 'n'
 *
 * @param n integer to count
 * @return unsigned char number of digits in the integer 'n'
 */
static unsigned char	count_numbers(int n)
{
	unsigned char	count;

	count = 1;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

// #include "libft.h"
// #include "unistd.h"
// #include <ctype.h>

// int main (void)
// {
// 	int number;

// 	number = 6515649;
// 	ft_putnbr_fd(number, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putstr_fd("6515649", 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putstr_fd(ft_itoa(number), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	number = 5111;
// 	ft_putnbr_fd(number, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putstr_fd("5111", 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putstr_fd(ft_itoa(number), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	number = -2568;
// 	ft_putnbr_fd(number, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putstr_fd("-2568", 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putstr_fd(ft_itoa(number), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	number = -97;
// 	ft_putnbr_fd(number, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putstr_fd("-97", 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putstr_fd(ft_itoa(number), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// }
