/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setunsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:08:41 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/02 20:10:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ms_getenv(t_prgm *glob, char *name)
{
	t_list		*node;

	if (!name || !glob->env)
	{
		glob->error = NULL_ARG_PASSED;
		return (NULL);
	}
	if ((node = ft_lstfind(glob->env, name, varcmp)))
		return (((t_variable *)node->data)->data);
	return (NULL);
}

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

int			ms_setenv(t_prgm *glob)
{
	t_list	*node;
	t_variable	template;

	if (replace_env(glob->env, glob->tab.av[1], glob->tab.av[2]))
		return (0);
	template.name = ft_strdup(glob->tab.av[1]);
	template.data = ft_strdup(glob->tab.av[2]);
	node = ft_lstnew(&template, sizeof(t_variable));
	ft_lstaddback(&glob->env, node);
	return (0);
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

int			ms_unsetenv(t_prgm *glob)
{
	int		i;

	if (glob->tab.ac < 2)
		return (glob->error = TOO_FEW_ARGS);
	i = 1;
	while (glob->tab.av[i])
		ft_lstremove_if(&glob->env, glob->tab.av[i++], varcmp, variable_delete);
	return (0);
}
