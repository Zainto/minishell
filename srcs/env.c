/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:08:41 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/05 02:53:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	**lsttotab(t_list *list)
{
	char		**tab;
	int			index;
	int			lstlen;
	t_variable	*tmp;

	if (!list)
		return (NULL);
	lstlen = ft_lstlen(list);
	index = 0;
	tab = malloc(sizeof(char *) * (lstlen + 1));
	ft_bzero(tab, sizeof(char *) * (lstlen + 1));
	while (index < lstlen)
	{
		tmp = list->data;
		ft_asprintf(&tab[index++], "%s=%s", tmp->name, tmp->data);
	}
	tab[index] = NULL;
	return (tab);
}

int		builtins_exec(t_prgm *glob)
{
	int		index;

	index = 0;
	while (glob->builtin[index].name)
	{
		if (ft_strequ(glob->builtin[index].name, glob->tab.av[0]))
			return (glob->builtin[index].builtin(glob));
		index++;
	}
	return (1);
}

int		env_setup(t_prgm *glob, t_local *local)
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
		local->envt = lsttotab(local->envl);
		if (!(local->to_del & EXECDEL))
			local->exec = glob->exec;
	}
	if (local->to_del & ENVLDEL || local->to_del & NOPARAM)
		ft_lstdel(&local->envl, variable_delete);
	return (glob->error);
}

int		env_handeler(t_prgm *glob)
{
	t_local	loc;
	t_list	*node;

	ft_bzero(&loc, sizeof(t_local));
	env_setup(glob, &loc);
	if (glob->status || glob->error)
		return (glob->error);
	if (builtins_exec(glob) != 1)
		return (glob->error);
	else if ((node = ft_lstfind(loc.exec, glob->tab.av[glob->tab.id], find_ex)))
		glob->error = launcher(glob, ((t_status *)node->data)->path, loc.envt);
	else if (ft_strnequ(glob->tab.av[glob->tab.id], "./", 2))
		glob->error = launcher(glob, glob->tab.av[glob->tab.id], loc.envt);
	else if (!glob->error)
		glob->error = WRONG_COMMAND;
	if (loc.to_del & EXECDEL)
		ft_dirdel(&loc.exec);
	ft_freetab(&loc.envt);
	return (glob->error < 0 ? glob->error : 1);
}
