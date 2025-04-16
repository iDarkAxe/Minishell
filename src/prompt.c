/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:24:58 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/06 16:24:46 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

char			*get_prompt_message(void);
static char		*get_hostname(void);
static char		*make_prompt(char **array);
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

/**
 * @brief Joins and adds the path to prompt
 *
 * @param array element in the prompts
 * @return char* final prompt
 */
static char	*make_prompt(char **array)
{
	char	*ptr;
	char	*ptr2;
	char	*path;
	char	buf[4096];

	ptr = ft_strjoins(array);
	add_to_garbage(ptr);
	if (ptr == NULL)
		return (ft_strdup_gb("Minishell$ "));
	path = getcwd(buf, 4096);
	if (path == NULL)
		return (ft_strdup_gb("Minishell$ "));
	ptr2 = ft_strjoins((char *[]){ptr, path, "$ ", NULL});
	free_element_gb(ptr);
	if (ptr2 == NULL)
		return (ft_strdup_gb("Minishell$ "));
	add_to_garbage(ptr2);
	return (ptr2);
}

/**
 * @brief Build the prompt message
 * If an error occurs, returns the defaut prompt message
 *
 * @return char* prompt message
 */
char	*get_prompt_message(void)
{
	char	*prompt;
	char	*hostname;
	char	*username;

	if (PROMPT_MESSAGE_CUSTOM == 0)
		return (ft_strdup_gb("Minishell$ "));
	hostname = get_hostname();
	if (hostname == NULL)
		return (ft_strdup_gb("Minishell$ "));
	username = getenv("USER");
	if (username == NULL)
	{
		free_element_gb(hostname);
		return (ft_strdup_gb("Minishell$ "));
	}
	prompt = make_prompt((char *[]){username, "@", hostname, ":", NULL});
	if (prompt == NULL)
		return (ft_strdup_gb("Minishell$ "));
	free_element_gb(hostname);
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
