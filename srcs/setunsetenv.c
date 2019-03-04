/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setunsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:08:41 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/04 21:37:00 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			replace_env(t_list *env, char *to_find, char *data)
{
	t_list		*node;
	t_variable	*tmp;

	if ((node = ft_lstfind(env, to_find, varcmp)))
	{
		tmp = node->data;
		ft_strdel(&tmp->data);
		tmp->data = ft_strdup(data);
		return (1);
	}
	return (0);
}

int			check_env(t_prgm *glob)
{
	char	**av;

	if (glob->tab.ac == 1)
		return (1);
	av = &glob->tab.av[1];
	while (*av)
	{
		if (ft_strchr(*av, '='))
			av++;
		else if (av[1])
			av += 2;
		else
			return (1);
	}
	return (0);
}

int			variabletolist(t_prgm *glob, t_list **envl, char *env)
{
	t_list		*node;
	t_variable	variable;
	int			eq;

	eq = ft_strcspn(env, "=");
	variable.name = ft_strsub(env, 0, eq);
	variable.data = ft_strsub(env, eq + 1, ft_strlen(env + eq));
	if (replace_env(*envl, variable.name, variable.data))
	{
		ft_strdel(&variable.name);
		ft_strdel(&variable.data);
		return (0);
	}
	if (!variable.name || !variable.data)
		return (glob->error = FAILED_MALLOC);
	if (!(node = ft_lstnew(&variable, sizeof(t_variable))))
		return (glob->error = FAILED_MALLOC);
	ft_lstadd(envl, node);
	return (0);
}

int			ms_setenv(t_prgm *glob)
{
	char	*holder;
	char	**av;

	if (check_env(glob))
		return (glob->error = WRONG_ARG_NUM);
	holder = NULL;
	av = &glob->tab.av[1];
	while (*av && !glob->error)
	{
		if(ft_strchr(*av, '='))
			holder = ft_strdup(*av++);
		else
		{
			if (ft_asprintf(&holder, "%s=%s", av[0], av[1]) < 0)
				return (glob->error = FAILED_MALLOC);
			av += 2;
		}
		variabletolist(glob, &glob->env, holder);
		ft_strdel(&holder);
	}
	return (glob->error);
}

void		variable_delete(void *data)
{
	t_variable	*tmp;

	tmp = (t_variable *)data;
	if (tmp->name)
		ft_strdel(&tmp->name);
	if (tmp->data)
		ft_strdel(&tmp->data);
}
