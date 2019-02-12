/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:08:41 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/12 06:10:22 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_prompt(t_prgm *glob)
{
	t_list	*env;
	t_env	*tmp;

	env = glob->env;
	if (glob->prompt)
		ft_strdel(&glob->prompt);
	while(env)
	{
		tmp = (t_env *)env->data;	
		if (ft_strequ(tmp->name, "PWD"))
		{
			glob->prompt = ft_strdup(ft_strrchr(tmp->data, '/') + 1);	
			break;
		}
		env = env->next;
	}
}

int		set_env(t_prgm *glob, char *name, char *data)
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

void	del_env(void *data)
{
	t_env	*tmp;

	tmp = (t_env *)data;
	if(tmp->name)
		ft_strdel(&tmp->name);
	if (tmp->data)
		ft_strdel(&tmp->data);
}

int		get_env(t_prgm *glob, char **env)
{
	t_list	*node;
	t_env	variable;
	int		eq;
	int		i;

	i = 0;
	while (env[i])
	{
		eq = ft_strcspn(env[i], "=");
		variable.name = ft_strsub(env[i], 0, eq);
		variable.data = ft_strsub(env[i], eq + 1, ft_strlen(env[i] + eq));
		node = ft_lstnew(&variable, sizeof(t_env));
		ft_lstaddback(&glob->env, node);
		i++;
	}
	get_prompt(glob);
	return (0);
}

void	print_env(t_list *node)
{
	t_env	*variable;

	variable = (t_env *)node->data;
	ft_printf ("%s=%s\n", variable->name, variable->data);
}
