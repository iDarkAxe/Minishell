/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:24:12 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/26 10:19:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include <signal.h>

/**
 * @brief Offset of return value of signals
 * 
 */
# ifndef SIG_OFFSET
#  define SIG_OFFSET 128
# endif

/**
 * @defgroup SIGNAL Signal related
 * @brief Signal related
 * @{
 */
extern sig_atomic_t	g_sig;
/** @} */
#endif
