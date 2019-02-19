/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 20:45:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/19 00:48:09 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# define DIR_MAX 1024

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
	char			**av;
	int				ac;
	unsigned long	error;
}					t_prgm;

int					envsetup(t_prgm *glob, char **env);
char				*ft_getenv(t_list *lst, char *name);
int					ft_setenv(t_prgm *glob, char *name, char *data);
void				print_env(t_list *node);
void				delenv(void *data);

int					builtin(t_prgm *glob, t_tab *args);
int					echo(t_tab *args);

t_list				*generate_path(t_prgm *glob);
void				print_exec(t_list *node);
#endif
