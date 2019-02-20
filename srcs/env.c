/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:08:41 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/20 04:06:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_prgm *glob, char *name)
{
	t_list	*lst;
	t_env	*tmp;

	if(!name || !glob->env)
	{
		glob->error = NULL_ARG;
		return (NULL);
	}
	lst = glob->env;
	while(lst)
	{
		tmp = (t_env *)lst->data;
		if (ft_strequ(tmp->name, name))
			return (tmp->data);
		lst = lst->next;
	}
	return(NULL);
}

int		ft_setenv(t_prgm *glob, char *name, char *data)
{
	t_list	*node;
	t_env	*tmp;
	t_env	template;

	if (!name)
		return (-1);
	node = glob->env;
	while (node)
	{
		tmp = node->data;
		if (ft_strequ(tmp->name, name))
		{
			ft_strdel(&tmp->data);
			tmp->data = ft_strdup(data);
			return (0);
		}
		node = node->next;
	}
	template.name = ft_strdup(name);
	template.data = ft_strdup(data);
	node = ft_lstnew(&template, sizeof(t_env));
	ft_lstaddback(&glob->env, node);
	return (0);
}

void	delenv(void *data)
{
	t_env	*tmp;

	tmp = (t_env *)data;
	if (tmp->name)
		ft_strdel(&tmp->name);
	if (tmp->data)
		ft_strdel(&tmp->data);
}

void	print_env(t_list *node)
{
	t_env	*variable;

	variable = (t_env *)node->data;
	ft_printf ("%s=%s\n", variable->name, variable->data);
}
