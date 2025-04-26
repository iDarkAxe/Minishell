/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:08:31 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/26 11:38:09 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdio.h"

/**
 * @brief Print the command structure with it's tokens
 * 
 * @param command command structure
 * @return ssize_t 0 is OK, otherwise error
 */
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
