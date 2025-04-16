/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:08:31 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/16 10:25:11 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdio.h"

ssize_t	print_command(t_command *command)
{
	t_command	*cmd;
	t_token		*token;

	if (!command)
		return (print_fd(2, "No command to print\n"));
	cmd = command;
	while (cmd)
	{
		printf("Command block at %p:\n", (void *)cmd);
		token = cmd->tokens;
		while (token)
		{
			printf("  Token: %s\n", token->str);
			token = token->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
