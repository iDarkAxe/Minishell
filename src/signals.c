/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:32:13 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/18 12:55:00 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "garbage.h"
#include "ft_printf.h"
#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include "ft_signal.h"
#include <stdlib.h>
#include <unistd.h>

void	signal_handler(int sig, siginfo_t *info, void *context);

sig_atomic_t	g_sig;

/**
 * @brief Main function for initialising signals
 *
 * @return int 0 if the function ends correctly, -1 otherwise.
 */
int	signal_init(void)
{
	struct sigaction	action_receive;

	action_receive.sa_sigaction = signal_handler;
	sigemptyset(&action_receive.sa_mask);
	action_receive.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGINT, &action_receive, NULL);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

/**
 * @brief Signal handler
 * Ctrl+C = SIGINT -> print "^C" and displays a new prompt on a new line.
 * Ctrl+\ = SIGQUIT -> do nothing
 *
 * Search for now signals :
 * stty -a | grep -Ewoe '(intr|quit|susp|erase|kill|eof|eol|eol2) = [^;]+';
  stty -a | grep -Ewoe '(swtch|start|stop|susp) = [^;]+';
  stty -a | grep -Ewoe '(rprnt|werase|lnext|discard) = [^;]+';
 *
 * @param sig Signal received.
 * @param info Information about the signal.
 * @param context Context of the signal.
 */
void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_sig = sig;
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

/**
 * @brief Function to reset signals to default
 *
 */
void	reset_signal_default(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_handler = SIG_DFL;
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

/**
 * @brief Function to ignore certain signals
 *
 */
void	ignore_signal(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_handler = SIG_IGN;
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}
