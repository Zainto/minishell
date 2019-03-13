/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:23:42 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/13 04:11:51 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int		generate_exec(t_prgm *glob, char *path)
{
	char		**tab;
	int			index;

	if (!path)
		return (glob->error = NULL_ARG_PASSED);
	index = 0;
	if (!(tab = ft_strsplit(path, ":")))
		return (glob->error = FAILED_MALLOC);
	while (tab[index])
		ft_dirlist(&glob->exec, tab[index++]);
	ft_freetab(&tab);
	return (glob->error = glob->exec ? 0 : FAILED_MALLOC);
}

int				execinit(t_prgm *glob)
{
	char	*path;

	if (glob->exec)
		ft_dirdel(&glob->exec);
	if (!(path = ft_strdup(ms_getenv(glob, &glob->env, "PATH"))))
		path = get_path(glob);
	if (generate_exec(glob, path))
		return (glob->error);
	ft_strdel(&path);
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
