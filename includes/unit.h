/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:42:10 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/01 01:14:47 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNITMINISHELL_H
# define UNITMINISHELL_H
# include "libft.h"
# include "minishell.h"
# include <stdlib.h>
# define BLUE "39"
# define ISTRUE 0
# define ISFALSE -1
# define T_CHMOD 766
# define HOME "/Users/cempassi"
# define NO_ENV_PATH "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:"
# define ENV_PATH "/Users/cempassi/.brew/bin:/Users/cempassi/Applications/bin:/usr/local/share:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/usr/local/munki"

void		glob_test_destructor(t_prgm *glob);
void		glob_test_init(t_prgm *glob);
int			test_envinit(void);
int			test_ms_getenv(void);
int			test_read_path(void);
int			test_execinit(void);
int			test_generate_exec(void);
int			test_get_exec(void);
int			test_line_processing(void);
int			test_replace_variable(void);
int			test_replace_home(void);
#endif
