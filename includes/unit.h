/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:42:10 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/20 08:20:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNITMINISHELL_H
# define UNITMINISHELL_H
# include "libft.h"
# include "minishell.h"
# include <stdlib.h>

# define NO_ENV_PATH "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:"
# define ENV_PATH "/Users/cempassi/.brew/bin:/Users/cempassi/Applications/bin:/usr/local/share:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/usr/local/munki"

void		glob_test_destructor(t_prgm *glob);
void		glob_test_init(t_prgm *glob);
int			test_envinit(void);
int			test_ft_getenv(void);
int			test_execinit(void);
int			test_get_path(void);
#endif
