/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:49:30 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 12:40:19 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int character);

/**
 * @brief Transform minuscules into majuscules
 *
 * @param character character to check
 * @return character in majuscule if was in minuscule
 * OR character isn´t minuscule
 */
int	ft_toupper(int character)
{
	if ((character >= 'a' && character <= 'z'))
		return (character - 32);
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
// 	test = toupper(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat Test : ", 1);
// 	test = ft_toupper(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);

// 	character = 'a';
// 	ft_putstr_fd("Resultat Attendu : ", 1);
// 	test = toupper(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat Test : ", 1);
// 	test = ft_toupper(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);

// 	character = 'f';
// 	ft_putstr_fd("Resultat Attendu : ", 1);
// 	test = toupper(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat Test : ", 1);
// 	test = ft_toupper(character);
// 	ft_putchar_fd(test, 1);
// 	ft_putendl_fd("", 1);
// }
