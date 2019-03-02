/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 20:45:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/02 19:53:30 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# define SPACE " \t\v\r"
# define DIR_MAX 1024
# define WRONG_COMMAND -1
# define FAILED_MALLOC -2
# define FAILED_OPEN -3
# define FAILED_CLOSE -4
# define FAILED_READ -5
# define UNCLOSED_COMMA -6
# define WRONG_CD_ARGS -7
# define TOO_FEW_ARGS -8
# define WRONG_CD_PATH -9
# define WRONG_EXIT_ARGS -10
# define WRONG_CD_TYPE -11
# define WRONG_ARG_NUM -12
# define WRONG_ARG_ENV_U -13
# define NULL_ARG_PASSED -14
# define EMPTY_LINE -15
# define DEFAULT_PATH "/etc/paths"
# define ENVLDEL 1
# define EXECDEL 2

typedef struct	s_prgm	t_prgm;
typedef int		(*t_built)(t_prgm *);

typedef struct		s_builtin
{
	char			*name;
	t_built			builtin;
}					t_builtin;

typedef struct 		s_variable
{
	char			*name;
	char			*data;
}					t_variable;

typedef struct		s_tab
{
	int				ac;
	int				id;
	char			**av;
}					t_tab;

typedef struct		s_local
{
	unsigned int	to_del;
	t_list			*envl;
	t_list			*exec;
	char			*path;
	char			**envt;
}					t_local;

typedef enum		e_error
{
	E_WRONG_COMMAND = WRONG_COMMAND,
	E_FAILED_MALLOC = FAILED_MALLOC,
	E_FAILED_OPEN = FAILED_OPEN,
	E_FAILED_CLOSE = FAILED_CLOSE,
	E_FAILED_READ = FAILED_READ,
	E_UNCLOSED_COMMA = UNCLOSED_COMMA,
	E_WRONG_CD_ARGS = WRONG_CD_ARGS,
	E_TOO_FEW_ARGS = TOO_FEW_ARGS,
	E_WRONG_CD_PATH = WRONG_CD_PATH,
	E_WRONG_EXIT_ARGS = WRONG_EXIT_ARGS,
	E_WRONG_CD_TYPE = WRONG_CD_TYPE,
	E_WRONG_ARG_NUM = WRONG_ARG_NUM,
	E_WRONG_ARG_ENV_U = WRONG_ARG_ENV_U,
	E_NULL_ARG = NULL_ARG_PASSED,
	E_EMPTY_LINE = EMPTY_LINE,
}					t_error;

struct 				s_prgm
{
	t_tab			tab;
	t_list			*env;
	t_list			*exec;
	char			*line;
	t_error			error;
	int				status;
	t_builtin		builtin[6];
	const char		*e_str[15];
};

int					initialization(t_prgm *glob, char **env);
int					env_handeler(t_prgm *glob);
void				error_manager(t_prgm *glob);

void				init_error(t_prgm *glob);
int					envinit(t_prgm *glob, char **env);
int					execinit(t_prgm *glob);
char				*read_path(t_prgm *glob);
void				init_builtin(t_prgm *glob);

int					get_exec(t_prgm *glob, char *path);
char				*ms_getenv(t_prgm *glob, char *name);
int					variabletolist(t_prgm *glob, t_list **envl, char *env);
void				variable_delete(void *data);
int					ms_setenv(t_prgm *glob);
int					replace_env(t_list *env, char *to_find, char *data);
int					ms_unsetenv(t_prgm *glob);
int					print_env(t_prgm *glob);

char				*get_path(t_prgm *glob);
char				*get_home(void);

void				print_variable(t_list *node);
int					var_filter(void *data, void *to_find);
int					process_line(t_prgm *glob);
int					replace_variable(t_prgm *glob);
int					replace_home(t_prgm *glob);
int					split_input(t_prgm *glob);

int					ms_env(t_prgm *glob);
int					echo(t_prgm *glob);
int					change_directory(t_prgm *glob);
int					ms_exit(t_prgm *glob);
int					env_option(t_prgm *glob, t_local *local);
int					builtins_exec(t_prgm *glob);
int					launcher(t_prgm *glob, char *exec, char **env);

int					find_exec(void *data, void *to_find);
int					varcmp(void *data, void *to_find);

int					generate_exec(t_prgm *glob, char *path);
void				print_exec(t_list *node);
#endif
