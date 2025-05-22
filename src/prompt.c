/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:24:58 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/22 17:21:39 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

char			*get_prompt_message(t_garbage *garbage);
static char		*get_hostname(t_garbage *garbage);
static char		*make_prompt(t_garbage *garbage, char **array);
static size_t	ft_strlen_and_choose_c(char *str, char c);

/**
 * @brief Search the index of a character
 *
 * @param str str to search from
 * @param c character searched
 * @return size_t index of character found OR 0 if not found
 */
static size_t	ft_strlen_and_choose_c(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str && str[i] != c)
		i++;
	return (i);
}

/**
 * @brief Get the hostname
 *
 * @return char* hostname
 */
static char	*get_hostname(t_garbage *garbage)
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
		close(fd_hostname);
		return (NULL);
	}
	close(fd_hostname);
	buf[buf_nbc] = '\0';
	get_hostname = ft_strndup(buf, ft_strlen_and_choose_c(buf, '.'));
	if (!get_hostname)
		return (NULL);
	add_to_garbage(garbage, get_hostname);
	return (get_hostname);
}

static char	*handle_colors(char **array)
{
	char	*str;

	if (array == NULL)
		return (NULL);
	if (PROMPT_COLOR == 1)
		str = ft_strjoins((char *[]){CYAN_COLOR, array[0], PURPLE_COLOR,
				array[1], "$ ", COLOR_OFF, "\n", DEFAULT_PROMPT, NULL});
	else
		str = ft_strjoins((char *[]){array[0], array[1], "$ ", NULL});
	return (str);
}

/**
 * @brief Joins and adds the path to prompt
 *
 * @param array element in the prompts
 * @return char* final prompt
 */
static char	*make_prompt(t_garbage *garbage, char **array)
{
	char	*userhost;
	char	*prompt;
	char	*path;
	char	buf[4096];

	if (array == NULL || array[1] == NULL)
		return (DEFAULT_PROMPT);
	userhost = ft_strjoins(array);
	if (userhost == NULL)
	{
		free_element_gb(garbage, array[2]);
		return (DEFAULT_PROMPT);
	}
	path = getcwd(buf, 4096);
	if (path == NULL)
	{
		free(userhost);
		return (DEFAULT_PROMPT);
	}
	prompt = handle_colors((char *[]){userhost, path, "$ ", NULL});
	free(userhost);
	if (prompt == NULL)
		return (DEFAULT_PROMPT);
	add_to_garbage(garbage, prompt);
	return (prompt);
}

/**
 * @brief Build the prompt message
 * If an error occurs, returns the static default prompt message
 *
 * @return char* prompt message
 */
char	*get_prompt_message(t_garbage *garbage)
{
	char	*prompt;
	char	*hostname;
	char	*username;

	if (PROMPT_MESSAGE_CUSTOM == 0)
		return (DEFAULT_PROMPT);
	hostname = get_hostname(garbage);
	if (hostname == NULL)
		return (DEFAULT_PROMPT);
	username = getenv("USER");
	if (username == NULL)
	{
		free_element_gb(garbage, hostname);
		return (DEFAULT_PROMPT);
	}
	prompt = make_prompt(garbage, (char *[]){username, "@", hostname, ":", NULL});
	if (prompt == NULL)
		return (DEFAULT_PROMPT);
	free_element_gb(garbage, hostname);
	return (prompt);
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
