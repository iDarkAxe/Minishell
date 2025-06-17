/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:06:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 13:11:16 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
* @brief Search a substring in a bigger string,
	up to len position in string
*
* @param big string to search in
* @param little	string to search
* @param len max size of big
* @return char* pointer to the first occurence of little in big
*/
const char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_size;
	size_t	count;

	count = 0;
	little_size = ft_strlen(little);
	if (little_size == 0 || little == big)
		return (&big[0]);
	if (len == 0 || *big == '\0' || ft_strlen(big) < little_size
		|| len < little_size)
		return (NULL);
	while (big[count] != '\0' && count <= (len - little_size))
	{
		if (ft_strncmp(&big[count], little, little_size) == 0)
			return (&big[count]);
		count++;
	}
	if (count > (len - little_size))
		return (NULL);
	return (&big[0]);
}

// #include <string.h>
// #include "libft.h"

// int main(void)
// {
//     char str[100] = "Je suis une chaine de caractere";
//     char str2[100] = "chaine";
//     char *result;
//     int fd = 1;

//     ft_putstr_fd("Resultat attendu   : ", fd);
//     ft_putstr_fd(strstr(str, str2), fd);
//     ft_putendl_fd("", fd);
//     ft_putstr_fd("Resultat test   : ", fd);
//     result = ft_strnstr(str, str2, ft_strlen(str));
//     if (result != NULL)
//         ft_putstr_fd(result, fd);
//     else
//         ft_putstr_fd("NULL", fd);
//     ft_putendl_fd("", fd);
//     ft_putendl_fd("     -----     ", fd);

//     ft_strlcpy(str2, "caractere", 5);
//     ft_putstr_fd("Resultat attendu   : ", fd);
//     ft_putstr_fd(strstr(str, str2), fd);
//     ft_putendl_fd("", fd);
//     ft_putstr_fd("Resultat test   : ", fd);
//     result = ft_strnstr(str, str2, ft_strlen(str));
//     if (result != NULL)
//         ft_putstr_fd(result, fd);
//     else
//         ft_putstr_fd("NULL", fd);
//     ft_putendl_fd("", fd);
//     ft_putendl_fd("     -----     ", fd);

//     ft_strlcpy(str, "abdEfghijkl", 5);
//     ft_strlcpy(str2, "sy", 5);
//     ft_putstr_fd("Resultat attendu   : ", fd);
//     result = strstr(str, str2);
//     if (result != NULL)
//         ft_putstr_fd(result, fd);
//     else
//         ft_putstr_fd("NULL", fd);
//     ft_putendl_fd("", fd);
//     ft_putstr_fd("Resultat test   : ", fd);
//     result = ft_strnstr(str, str2, 1);
//     if (result != NULL)
//         ft_putstr_fd(result, fd);
//     else
//         ft_putstr_fd("NULL", fd);
//     ft_putendl_fd("", fd);
// }
