/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:03:51 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/14 13:06:02 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include <stddef.h>

typedef struct s_var		t_var;
typedef struct s_env_vars	t_env_vars;
typedef struct s_params		t_params;

struct						s_env_vars
{
	t_var					*head_var;
	size_t					count;
};

struct						s_var
{
	t_var					*next;
	char					*value;
	t_params				*head_params;
	size_t					count;
};

struct						s_params
{
	t_params				*next;
	char					*value;
};

// Utils
size_t						ft_strlen_choose_c(const char *str, char c);
t_var						*ft_varlast(t_var *var);
void						ft_varsadd_back(t_var **var, t_var *new);
t_params					*ft_paramlast(t_params *params);
void						ft_paramsadd_back(t_params **params, t_params *new);

t_env_vars					*get_env(char *envp[]);

#endif
