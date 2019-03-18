/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 00:12:34 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/18 11:03:11 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <limits.h>

static int			home_checker(t_prgm *glob, t_list **env)
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

static int			oldpwd_checker(t_prgm *glob, t_list **env)
{
	char	*holder;
	char	path[PATH_MAX];

	holder = NULL;
	if (!ft_lstfind(*env, OPW, varcmp))
	{
		if (!(ft_asprintf(&holder, "OLDPWD=%s", getcwd(path, PATH_MAX))))
			return (glob->error = FAILED_MALLOC);
		variabletolist(glob, env, holder);
		ft_strdel(&holder);
	}
	return (0);
}

static int			pwd_checker(t_prgm *glob, t_list **env)
{
	char	*holder;
	char	path[PATH_MAX];

	holder = NULL;
	if (!ft_lstfind(*env, "PWD", varcmp))
	{
		if (!(ft_asprintf(&holder, "PWD=%s", getcwd(path, PATH_MAX))))
			return (glob->error = FAILED_MALLOC);
		variabletolist(glob, env, holder);
		ft_strdel(&holder);
	}
	return (0);
}

int					var_checker(t_prgm *glob, t_list **env, char *name)
{
	int		result;

	result = 0;
	if (ft_strequ(name, "HOME"))
		result = home_checker(glob, env);
	else if (ft_strequ(name, "PWD"))
		result = pwd_checker(glob, env);
	else if (ft_strequ(name, OPW))
		result = oldpwd_checker(glob, env);
	return (result);
}
