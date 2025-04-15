/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:08:31 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/15 10:49:48 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdio.h"

ssize_t	print_command(t_command *command)
{
	t_command	*cmd;
	t_token		*token;

	if (!command)
		return (write(2, "No command to print\n", 20));
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
