/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:08:41 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/01 06:53:50 by cempassi         ###   ########.fr       */
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

	lstlen = ft_lstlen(list);
	index = 0;
	tab = malloc(sizeof(char *) * (lstlen + 1));
	ft_bzero(tab, sizeof(char *) * (lstlen + 1));
	while (index < lstlen)
	{
		tmp = list->data;
		ft_asprintf(&tab[index++], "%s=%s",tmp->name, tmp->data);
	}
	tab[index] = NULL;
	return (tab);
}

int		env_setup(t_prgm *glob, t_local *local)
{
	if (glob->tab.ac == 1 && ft_strequ(glob->tab.av[0], "env"))
		return (print_env(glob));
	local->envt = lsttotab(glob->env);
	local->exec = glob->exec;
	return (0);
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

int		env_handeler(t_prgm *glob)
{
	t_local	local;
	t_list	*node;

	ft_bzero(&local, sizeof(t_local));
	if (builtins_exec(glob) <= 0)
		return (glob->error);
	if (env_setup(glob, &local))
		return (0);
	if ((node = ft_lstfind(local.exec, glob->tab.av[glob->tab.id], find_exec)))
	{
		launcher(glob, node->data, local.envt);
		ft_freetab(&local.envt);
		return (0);
	}
	return (1);
}
