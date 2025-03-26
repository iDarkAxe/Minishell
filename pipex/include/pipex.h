/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eveil <eveil@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:50:55 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/26 11:52:54 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_fd
{
	int		first_pipe[2];
	int		infile;
	int		outfile;

}			t_fd;

typedef struct s_data
{
	t_fd	fd;
	size_t	i;
	int		pid_1;
	int		pid_2;
	int		status;
	char	*pathname;
	char	*path_bin;
	char	*path;
	char	**commands;
	char	**all_paths;
	char	buf[4096];
	t_bool	path_is_empty;
}			t_data;

char		**get_path_bins(t_data *data, char *envp[]);

void		last_child(t_data *data, char *envp[], char *argv[]);
void		first_child(t_data *data, char *envp[], char *argv[]);
void		one_conmmand(t_data *data, char *envp[], char *argv[]);
void		exec_command(t_data *data, char *envp[], char *command);
void		free_and_close_all(t_data *data);
int			exec(int argc, char **argv, char **envp);

// Utils
char		*str_two_join(char *str, char *str_2, char *str_3);
char		**free_double_array(char **strs);

#endif
