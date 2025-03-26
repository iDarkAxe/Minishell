/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveil <eveil@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:02:16 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/17 16:53:16 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_fds(t_data *data)
{
	if (data->fd.first_pipe[0] != -1)
		close(data->fd.first_pipe[0]);
	if (data->fd.first_pipe[1] != -1)
		close(data->fd.first_pipe[1]);
	if (data->fd.infile != -1)
		close(data->fd.infile);
	if (data->fd.outfile != -1)
		close(data->fd.outfile);
}

void	free_and_close_all(t_data *data)
{
	if (!data)
		return ;
	if (data->all_paths)
	{
		free_double_array(data->all_paths);
		data->all_paths = NULL;
	}
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
	close_fds(data);
}
