/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:24:58 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/20 11:02:14 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

size_t	ft_strlen_and_choose_c(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str && str[i] != c)
		i++;
	return (i);
}

char	*read_prompt(char *prompt)
{
	char	*str;

	str = readline(prompt);
	return (str);
}

char	*str_two_join(char *str, char *str_2, char *str_3)
{
	char	*temp_str;
	char	*final_str;

	if (!str || !str_2 || !str_3)
		return (NULL);
	temp_str = ft_strjoin(str, str_2);
	if (!temp_str)
		return (NULL);
	final_str = ft_strjoin(temp_str, str_3);
	free(temp_str);
	if (!final_str)
		return (NULL);
	return (final_str);
}

char	*get_user_hostname_and_current_repo(void)
{
	char	*username;
	char	*display;
	char	*get_hostname;
	char	buf[4096];
	int		fd_hostname;
	size_t	buf_nbc;

	username = getenv("USER");
	fd_hostname = open("/etc/hostname", O_RDONLY); 
	if (fd_hostname == -1)
		exit(EXIT_FAILURE);
	buf_nbc = read(fd_hostname, buf, 25);
	if (buf_nbc == 0)
		exit(EXIT_FAILURE);
	buf[buf_nbc] = '\0';
	get_hostname = ft_strndup(buf, ft_strlen_and_choose_c(buf, '.'));
	display = ft_strjoins((char *[]){username,"@", get_hostname, ":", getcwd(buf, 4096), "$ ", NULL});
	if (!display)
	{
		free(username);
		exit(EXIT_FAILURE);
	}
	free(get_hostname);
	close(fd_hostname);
	return (display);
}

// int		main(void)
// {
// 	char	*prompt;
// 	char	*display;
	
// 	display = get_user_hostname_and_current_repo();
// 	if (!display)
// 		return (1);
// 	// while (1)
// 	prompt = read_prompt(display);
// 	free(display);
// 	free(prompt);
// 	return (0);	
// }
