/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 20:45:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/20 07:47:39 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# define DIR_MAX 1024
# define NULL_ARG -1
# define FAILED_MALLOC -2
# define FAILED_OPEN -3
# define FAILED_CLOSE -4
# define DEFAULT_PATH "/etc/paths"

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

typedef enum		e_error
{
	E_NULL_ARG = NULL_ARG,
	E_FAILED_MALLOC = FAILED_MALLOC,
	E_FAILED_OPEN = FAILED_OPEN,
	E_FAILED_CLOSE = FAILED_CLOSE,
}					t_error;

typedef struct		s_prgm
{
	t_list			*args;
	t_list			*env;
	t_list			*exec;
	t_tab			*tab;
	char			*line;
	char			**av;
	int				ac;
	t_error			error;
}					t_prgm;

void				init_minishell(t_prgm *glob, int ac, char **av, char **env);
int					execinit(t_prgm *glob);
int					envinit(t_prgm *glob, char **env);
char				*ft_getenv(t_prgm *glob, char *name);
int					ft_setenv(t_prgm *glob, char *name, char *data);
void				print_env(t_list *node);
void				delenv(void *data);

int					builtin(t_prgm *glob, t_tab *args);
int					echo(t_tab *args);

char				*get_path(t_prgm *glob);
t_list				*generate_path(t_prgm *glob);
void				print_exec(t_list *node);
#endif
