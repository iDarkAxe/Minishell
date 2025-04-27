/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:12:58 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/27 13:10:24 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

char	*ft_filler(int fd, char *backup);
char	*ft_make_line(char *buffer, char *backup);
char	*ft_strjoin_gnl(char *s1, char const *s2);

/**
 * @brief Main function : 
 * Get the next line of a file descriptor
 * Stops if '\'n is detected or it there's nothing to read
 * /!\ Needs to be freed after use
 *
 * @param fd File descriptor
 * @return char* Next line of the file
 */
char	*get_next_line(int fd)
{
	static char	backup[BUFFER_SIZE + 1] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_filler(fd, backup);
	if (line == NULL || line[0] == '\0')
		return ((void)free(line), NULL);
	return (line);
}

/**
 * @brief Fills 'backup', stores in a buffer, 
 * Stops if '\'n is detected or it there's nothing to read
 * Read of fixed size at compilation (default is 42 bytes)
 *
 * @param fd File descriptor
 * @param backup Backup of the buffer
 * @return char* Next line of the file
 */
char	*ft_filler(int fd, char *backup)
{
	char	*buffer;
	ssize_t	read_return;

	read_return = 1;
	buffer = NULL;
	while (read_return > 0)
	{
		if (backup[0] == '\0')
		{
			read_return = read(fd, backup, BUFFER_SIZE);
			if (read_return < 0)
				return ((void)free(buffer), NULL);
			backup[read_return] = '\0';
		}
		buffer = ft_strjoin_gnl(buffer, backup);
		if (buffer == NULL)
			return (NULL);
		backup[0] = '\0';
		if (ft_strchr(buffer, '\n'))
			return (ft_make_line(buffer, backup));
	}
	return (buffer);
}

/**
 * @brief Build a new array containing the new line
 * and stores the rest of buffer into backup
 *
 * @param buffer Buffer to extract the line from
 * @param backup Rest of the buffer
 * @return char* Array containing the new line
 */
char	*ft_make_line(char *buffer, char *backup)
{
	size_t	index;
	size_t	j;
	char	*line;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	index = 0;
	while (buffer[index] != '\0' && buffer[index] != '\n')
		index++;
	line = malloc(sizeof(char) * (index + 2));
	if (!line)
		return ((void)free(buffer), NULL);
	j = 0;
	while (j <= index)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';
	index = 0;
	while (buffer[j] != '\0')
		backup[index++] = buffer[j++];
	backup[index] = '\0';
	free(buffer);
	return (line);
}

/**
 * @brief Copies s1 in a new array and concatenates s2
 * 
 * @param pointer String to copy in
 * @param s1 First array to copy from
 * @param s2 Second array to concatenate
 * @return char* Array containing s1 and s2
 */
static char	*ft_cpy_cat_gnl(char *pointer, char const *s1, char const *s2)
{
	size_t	index;
	size_t	s1_len;

	index = 0;
	while (s1[index] != '\0')
	{
		pointer[index] = s1[index];
		index++;
	}
	s1_len = index;
	index = 0;
	while (s2[index] != '\0')
	{
		pointer[s1_len + index] = s2[index];
		index++;
	}
	pointer[s1_len + index] = '\0';
	return (pointer);
}

/**
 * @brief Modified strjoin to work with GNL
 * 
 * @param s1 First array to copy from
 * @param s2 Second array to concatenate
 * @return char* Array containing s1 and s2
 */
char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char	*pointer;
	size_t	s2_len;
	size_t	s1_len;

	s2_len = 0;
	while (s2[s2_len] != '\0')
		s2_len++;
	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	s1_len = 0;
	while (s1[s1_len] != '\0')
		s1_len++;
	pointer = malloc(s1_len + s2_len + 1);
	if (pointer == NULL)
		return ((void)free(s1), NULL);
	pointer = ft_cpy_cat_gnl(pointer, s1, s2);
	free(s1);
	return (pointer);
}
