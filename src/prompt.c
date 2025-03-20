/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:24:58 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/20 11:02:25 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

static size_t	ft_strlen_and_choose_c(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str && str[i] != c)
		i++;
	return (i);
}

static char	*read_prompt(char *prompt)
{
	char	*str;

	str = readline(prompt);
	return (str);
}

static char	*get_hostname_join_message(char *username)
{
	char	*display;
	char	*get_hostname;
	char	buf[4096];
	int		fd_hostname;
	size_t	buf_nbc;

	fd_hostname = open("/etc/hostname", O_RDONLY); 
	if (fd_hostname == -1)
	{
		perror("");
		return (NULL);
	}
	buf_nbc = read(fd_hostname, buf, 25);
	if (buf_nbc == 0)
	{
		perror("");
		return (NULL);
	}
	close(fd_hostname);
	buf[buf_nbc] = '\0';
	get_hostname = ft_strndup(buf, ft_strlen_and_choose_c(buf, '.'));
	if (!get_hostname)
		return (NULL);
	display = ft_strjoins((char *[]){username,"@", get_hostname, ":", getcwd(buf, 4096), "$ ", NULL});
	if (!display)
		return (NULL);
	free(get_hostname);
	return (display);
}

char	*get_prompt_message(void)
{
	char	*username;
	char	*prompt_message;

	username = getenv("USER");
	prompt_message = get_hostname_join_message(username);
	if (!prompt_message)
		return (NULL);
	return (prompt_message);
}

// int		main(void)
// {
// 	char	*prompt;
// 	char	*display;
//
// 	display = get_prompt_message();	
// 	if (!display)
// 		return (1);
// 	while (1)
// 		prompt = read_prompt(display);
// 	free(display);
// 	free(prompt);
// 	return (0);	
// }
