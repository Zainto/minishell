/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:08:41 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/18 11:17:37 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static char	**lsttotab(t_list *list)
{
	char		**tab;
	int			index;
	int			lstlen;
	t_variable	*tmp;

	if (!list)
		return (NULL);
	lstlen = ft_lstlen(list);
	index = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (lstlen + 1))))
		return (NULL);
	ft_bzero(tab, sizeof(char *) * (lstlen + 1));
	while (index < lstlen)
	{
		tmp = list->data;
		ft_asprintf(&tab[index], "%s=%s", tmp->name, tmp->data);
		index++;
		list = list->next;
	}
	tab[index] = NULL;
	index = 0;
	return (tab);
}

static int	local_exec(t_prgm *glob, t_local *local)
{
	char		**tab;
	int			index;
	char		*path;

	if (!(path = ms_getenv(glob, &local->envl, "PATH")))
		return (0);
	index = 0;
	if (!(tab = ft_strsplit(path, ":")))
		return (glob->error = FAILED_MALLOC);
	while (tab[index])
		ft_dirlist(&local->exec, tab[index++]);
	ft_freetab(&tab);
	return (0);
}

static int	builtins_exec(t_prgm *glob, t_local *local)
{
	int		index;

	index = 0;
	while (glob->builtin[index].name)
	{
		if (ft_strequ(glob->builtin[index].name, glob->tab.av[0]))
		{
			ft_dirdel(&local->exec);
			ft_freetab(&local->envt);
			return (glob->builtin[index].builtin(glob));
		}
		index++;
	}
	return (1);
}

static int	env_setup(t_prgm *glob, t_local *local)
{
	if (ft_strequ(glob->tab.av[0], "env"))
	{
		glob->tab.id = 1;
		env_options(glob, local);
	}
	if (!glob->error && !glob->status)
	{
		if (!local->envl && !(local->to_del & ENVLDEL))
			local->envl = glob->env;
		if (!(local->envt = lsttotab(local->envl))
				&& !(local->to_del & ENVLDEL))
			glob->error = FAILED_MALLOC;
		local_exec(glob, local);
	}
	if (local->to_del & ENVLDEL || local->to_del & NOPARAM)
		ft_lstdel(&local->envl, variable_delete);
	return (glob->error);
}

int			env_handeler(t_prgm *glob)
{
	t_local	loc;
	t_list	*node;

	ft_bzero(&loc, sizeof(t_local));
	env_setup(glob, &loc);
	if (glob->status || glob->error)
		return (glob->error);
	if (builtins_exec(glob, &loc) != 1)
		return (glob->error);
	else if ((node = ft_lstfind(loc.exec, glob->tab.av[glob->tab.id], find_ex)))
		glob->error = launcher(glob, ((t_status *)node->data)->path, loc.envt);
	else if (ft_strnequ(glob->tab.av[glob->tab.id], "./", 2))
		glob->error = launcher(glob, glob->tab.av[glob->tab.id], loc.envt);
	else if (glob->tab.av[glob->tab.id][0] == '/')
		glob->error = launcher(glob, glob->tab.av[glob->tab.id], loc.envt);
	else if (!glob->error)
		glob->error = WRONG_COMMAND;
	ft_dirdel(&loc.exec);
	ft_freetab(&loc.envt);
	return (glob->error < 0 ? glob->error : 1);
}
