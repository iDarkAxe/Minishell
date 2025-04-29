/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:03:51 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/29 10:25:39 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include <stddef.h>

typedef struct s_var		t_var;
typedef struct s_env_vars	t_env_vars;
typedef struct s_params		t_params;
typedef	struct s_swap		t_swap;

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

struct						s_swap
{
    t_var *prev_str;
    t_var *prev_str_1;
    t_var *curr_str; 
    t_var *curr_str_1; 
    t_var *curr;
    t_var *curr_1;
    t_var *temp;
};

// Utils
size_t		ft_strlen_choose_c(const char *str, char c);
int		ft_strcmp(const char *s1, const char *s2);
t_var		*ft_varlast(t_var *var);
void		ft_varsadd_back(t_var **var, t_var *new);
t_params	*ft_paramlast(t_params *params);
void		ft_paramsadd_back(t_params **params, t_params *new);
void		print_env_vars(t_env_vars *env);

t_env_vars	*get_env(char *envp[]);
t_env_vars	*copy_env(t_env_vars *env);
int		count_env(t_env_vars env);
void		swap_vars(t_var **head, char *str, char *str_1);
void		sort_ascii_order(t_env_vars *env);
char		*search_env(t_env_vars *env, char *var);

#endif
