/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:48:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/04 23:16:28 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		varcopy(void *dest, void *source)
{
	t_variable		*dst;
	t_variable		*src;

	dst = dest;
	src = source;
	if (!(dst->name = ft_strdup(src->name)))
		return (-1);
	if (!(dst->data = ft_strdup(src->data)))
		return (-1);
	return (0);
}

int		env_i(t_prgm *glob, t_local *local, int id)
{
	t_prgm		tmp;

	ft_lstdel(&local->envl, NULL);
	ft_bzero(&tmp, sizeof(t_prgm));
	local->to_del |= ENVLDEL;
	while (ft_strchr(glob->tab.av[id], '='))
		variabletolist(glob, &local->envl, glob->tab.av[id++]);
	if (!glob->tab.av[id])
		glob->error = EMPTY_LINE;
	return (id);
}

int		env_u(t_prgm *glob, t_local *local, int id)
{
	local->to_del |= ENVLDEL;
	if (!(local->envl = ft_lstcpy(glob->env, varcopy)))
		return (glob->error = FAILED_MALLOC);
	local->envl = ft_lstfilter(local->envl, glob->tab.av[id], var_filter);
	++id;
	return (id);
}

int		env_simple(t_prgm *glob, t_local *local, int id)
{
	if (glob->tab.ac > 1)
	{
		local->to_del |= ENVLDEL;
		if (!(local->envl = ft_lstcpy(glob->env, varcopy)))
			return (glob->error = FAILED_MALLOC);
		while (ft_strchr(glob->tab.av[id], '='))
			variabletolist(glob, &local->envl, glob->tab.av[id++]);
	}
	else
		local->envl = glob->env;
	if (glob->tab.av[id])
		return (id);
	glob->status = print_env(local->envl);
	return (id);
}

int		env_options(t_prgm *glob, t_local *local)
{
	if (ft_strchr(glob->tab.av[glob->tab.id], '=') || glob->tab.ac == 1)
		glob->tab.id = env_simple(glob, local, glob->tab.id);
	if (local->to_del)
		return (0);
	if (ft_strequ(glob->tab.av[glob->tab.id], "-u"))
		glob->tab.id = env_u(glob, local, ++glob->tab.id);
	if (ft_strequ(glob->tab.av[glob->tab.id], "-i"))
		glob->tab.id = env_i(glob, local, ++glob->tab.id);
	if (!glob->tab.av[glob->tab.id] || glob->tab.av[glob->tab.id][0] != '-')
		return (0);
	return (env_options(glob, local));
}
