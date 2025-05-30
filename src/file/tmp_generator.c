/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:10:41 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/30 11:24:17 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "garbage.h"
#include "libft.h"
#include "ft_printf.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>

static char		*ft_random(void);
static t_tmp	try_create_tmp(t_garbage *garbage, char *path);

/**
 * @brief Create a tmp file, verify if it already exist,
 * tries to open it to verify permissions, and returns the result
 *
 * @param garbage garbage structure
 * @param path path where to create the file
 * @param nbr_try number of try to create a tmp file
 * @return t_tmp structure with the path+name of created name
 */
t_tmp	create_tmp(t_garbage *garbage, char *path, int nbr_try)
{
	t_tmp	tmp;

	nbr_try--;
	tmp = try_create_tmp(garbage, path);
	if (nbr_try < 0)
	{
		tmp.fd = -1;
		return (tmp);
	}
	if (tmp.fd == -1 || tmp.name == NULL)
		return (tmp);
	if (access(tmp.name, F_OK) == 0)
	{
		free_element_gb(garbage, tmp.name);
		tmp = create_tmp(garbage, path, nbr_try);
		return (tmp);
	}
	tmp.fd = open(tmp.name, O_RDWR | O_CREAT, 0644);
	if (tmp.fd < 0)
	{
		free_element_gb(garbage, tmp.name);
		tmp = create_tmp(garbage, path, nbr_try);
		return (tmp);
	}
	return (tmp);
}

/**
 * @brief Try to generate a name of a temporary file
 *
 * @param path path where to create the file
 * @return t_tmp structure with the path+name of created name
 */
static t_tmp	try_create_tmp(t_garbage *garbage, char *path)
{
	char	*name;
	t_tmp	tmp;

	if (path == NULL)
		path = "/tmp/";
	tmp.fd = 3;
	name = ft_random();
	if (name == NULL)
	{
		ft_dprintf(2, "Couldn't generate a random\n");
		tmp.fd = -1;
		return (tmp);
	}
	add_to_garbage(garbage, name);
	tmp.name = ft_strjoins((char *[]){path, "minishell_tmp_", name, NULL});
	free_element_gb(garbage, name);
	if (tmp.name == NULL)
	{
		tmp.fd = -1;
		return (tmp);
	}
	add_to_garbage(garbage, tmp.name);
	return (tmp);
}

/**
 * @brief Generator of random string of numbers
 *
 * @return char* array of digits
 */
static char	*ft_random(void)
{
	int		fd;
	int		random_nbr;
	char	*random_str;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	random_nbr = -2147483648;
	while (random_nbr == -2147483648)
	{
		if (read(fd, &random_nbr, sizeof(int)) == -1)
		{
			close(fd);
			return (NULL);
		}
		if (random_nbr < 0)
			random_nbr = -random_nbr;
	}
	close(fd);
	random_str = ft_itoa(random_nbr);
	return (random_str);
}
