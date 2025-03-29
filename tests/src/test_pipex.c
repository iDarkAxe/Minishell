/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:32:21 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/29 14:39:37 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	exec(4, (char *[]){"/dev/fd/4", "cat", "/dev/fd/5", NULL}, envp);
	return (0);
}
