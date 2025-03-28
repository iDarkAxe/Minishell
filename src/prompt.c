/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:24:58 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/26 13:59:38 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

char			*get_prompt_message(void);

static size_t	ft_strlen_and_choose_c(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str && str[i] != c)
		i++;
	return (i);
}

static char	*get_hostname(void)
{
	char	*get_hostname;
	int		fd_hostname;
	char	buf[4096];
	ssize_t	buf_nbc;

	fd_hostname = open("/etc/hostname", O_RDONLY);
	if (fd_hostname == -1)
	{
		perror("");
		return (NULL);
	}
	buf_nbc = read(fd_hostname, buf, 4096 - 1);
	if (buf_nbc == 0)
	{
		perror("");
		return (NULL);
	}
	close(fd_hostname);
	buf[buf_nbc] = '\0';
	get_hostname = ft_strndup(buf, ft_strlen_and_choose_c(buf, '.'));
	add_to_garbage(get_hostname);
	if (!get_hostname)
		return (NULL);
	return (get_hostname);
}

static char	*join_message(char *username)
{
	char	*display;
	char	*hostname;
	char	buf[4096];

	hostname = get_hostname();
	display = ft_strjoins((char *[]){username, "@", hostname, ":",
			getcwd(buf, 4096), "$ ", NULL});
	add_to_garbage(display);
	free_element_gb(hostname);
	if (!display)
		return (NULL);
	return (display);
}

char	*get_prompt_message(void)
{
	char	*username;
	char	*prompt_message;

	if (PROMPT_MESSAGE_CUSTOM == 0)
		return (ft_strdup_gb("Minishell$ "));
	username = getenv("USER");
	prompt_message = join_message(username);
	if (prompt_message == NULL)
		return (ft_strdup_gb("Minishell$ "));
	return (prompt_message);
}

// int	main(void)
// {
// 	char	*prompt;
// 	char	*display;
//
// 	display = get_prompt_message();
// 	if (!display)
// 		return (1);
// 	while (1)
// 		prompt = readline(display);
// 	free(display);
// 	free(prompt);
// 	return (0);
// }
