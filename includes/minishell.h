/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 20:45:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/12 05:51:23 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# define DIR_MAX 512

typedef struct 		s_env
{
	char	*name;
	char	*data;
}					t_env;

typedef struct		s_tab
{
	int		ac;
	char	**av;
}					t_tab;

typedef struct		s_prgm
{
	char			dir[DIR_MAX];
	t_list			*args;
	t_list			*env;
	char			*line;
	char			*prompt;
	unsigned long	error;
}					t_prgm;

int					get_env(t_prgm *glob, char **env);
int					set_env(t_prgm *glob, char *name, char *data);
void				get_prompt(t_prgm *glob);
void				print_env(t_list *node);
int					unset_env(t_prgm *glob, char *name);
void				del_env(void *data);

int					builtin(t_prgm *glob, t_tab *args);
int					echo(t_tab *args);
#endif
