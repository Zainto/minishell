/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 00:12:34 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/05 00:25:39 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int			home_checker(t_prgm *glob, t_list **env)
{
	char	*holder;

	holder = NULL;
	if (!ft_lstfind(*env, "HOME", varcmp))
	{
		if (!(holder = get_home(glob)))
			return (glob->error = FAILED_MALLOC);
		variabletolist(glob, env, holder);
		ft_strdel(&holder);
	}
	return (0);
}

int			path_checker(t_prgm *glob, t_list **env)
{
	char	*holder;

	holder = NULL;
	if (!ft_lstfind(*env, "PATH", varcmp))
	{
		if (!(ft_asprintf(&holder, "PATH=%s", get_path(glob))))
			return (glob->error = FAILED_MALLOC);
		variabletolist(glob, env, holder);
		execinit(glob);
		ft_strdel(&holder);
	}
	return (0);
}

int			pwd_checker(t_prgm *glob, t_list **env)
{
	char	*holder;

	holder = NULL;
	if (!ft_lstfind(*env, "PWD", varcmp))
	{
		if (!(ft_asprintf(&holder, "PWD=%s", getcwd(NULL, 0))))
			return (glob->error = FAILED_MALLOC);
		variabletolist(glob, env, holder);
		ft_strdel(&holder);
	}
	return (0);
}
