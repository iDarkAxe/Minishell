/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:54:11 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 12:40:10 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int character);

/**
 * @brief Transform majuscules into minuscules
 *
 * @param character character to check
 * @return character in minuscules if was in majuscules
	OR character isn´t majuscules
 */
int	ft_tolower(int character)
{
	if ((character >= 'A' && character <= 'Z'))
		return (character + 32);
	return (character);
}

// #include "libft.h"
// #include <ctype.h>

// int main(void)
// {
// 	int character;
// 	int test;

// 	character = 'A';
// 	ft_putstr_fd("Resultat Attendu : ", 1);
// 	test = tolower(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat Test : ", 1);
// 	test = ft_tolower(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);

// 	character = 'a';
// 	ft_putstr_fd("Resultat Attendu : ", 1);
// 	test = tolower(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat Test : ", 1);
// 	test = ft_tolower(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);

// 	character = 'f';
// 	ft_putstr_fd("Resultat Attendu : ", 1);
// 	test = tolower(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat Test : ", 1);
// 	test = ft_tolower(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// }
