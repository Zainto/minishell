/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:23:42 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/18 11:13:08 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int				execinit(t_prgm *glob)
{
	char	*path;
	char	*holder;

	holder = NULL;
	if (!(path = ms_getenv(glob, &glob->env, "PATH")))
	{
		path = get_path(glob);
		ft_asprintf(&holder, "PATH=%s", path);
		variabletolist(glob, &glob->env, holder);
		ft_strdel(&holder);
		ft_strdel(&path);
	}
	return (0);
}

static void		init_builtin(t_prgm *glob)
{
	glob->builtin[0].name = "echo";
	glob->builtin[0].builtin = echo;
	glob->builtin[1].name = "cd";
	glob->builtin[1].builtin = change_directory;
	glob->builtin[2].name = "setenv";
	glob->builtin[2].builtin = ms_setenv;
	glob->builtin[3].name = "unsetenv";
	glob->builtin[3].builtin = ms_unsetenv;
	glob->builtin[4].name = "exit";
	glob->builtin[4].builtin = ms_exit;
	glob->builtin[5].name = NULL;
}

static int		envinit(t_prgm *glob, char **env)
{
	int				i;
	int				shlvl;
	char			*holder;

	i = 0;
	if (env)
	{
		while (env[i])
			if (variabletolist(glob, &glob->env, env[i++]))
				return (glob->error = FAILED_MALLOC);
	}
	if ((shlvl = ft_atoi(ms_getenv(glob, &glob->env, "SHLVL"))))
	{
		shlvl++;
		holder = NULL;
		ft_asprintf(&holder, "%s=%d", "SHLVL", shlvl);
		variabletolist(glob, &glob->env, holder);
		ft_strdel(&holder);
	}
	else
		variabletolist(glob, &glob->env, "SHLVL=1");
	return (0);
}

int				initialization(t_prgm *glob, char **env)
{
	ft_bzero(glob, sizeof(t_prgm));
	init_error(glob);
	init_builtin(glob);
	if (envinit(glob, env) || execinit(glob))
	{
		error_manager(glob);
		return (-1);
	}
	return (0);
}
