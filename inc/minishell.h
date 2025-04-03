/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/03 17:10:17 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H 
# define MINISHELL_H

# ifndef PROMPT_MESSAGE_CUSTOM
#  define PROMPT_MESSAGE_CUSTOM 1
# endif

# define TMP_PATH "/tmp/"

typedef struct s_tmp
{
	char	*name;
	int		fd;
}			t_tmp;

int		signal_init(void);
char	*get_prompt_message(void);
t_tmp	create_tmp(char *path, int nbr_try);

#endif 
