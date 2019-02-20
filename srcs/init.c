/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:23:42 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/20 08:24:33 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_minishell(t_prgm *glob, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	ft_bzero(glob, sizeof(t_prgm));
	envinit(glob, env);
}

int			execinit(t_prgm *glob)
{
	char	*path;
	
	path = get_path(glob);
	//error_check;
	return (-1);	
}

static int	variabletolist(t_prgm *glob, char *env)
{
	t_list	*node;
	t_env	variable;
	int		eq;

	eq = ft_strcspn(env, "=");
	variable.name = ft_strsub(env, 0, eq);
	variable.data = ft_strsub(env, eq + 1, ft_strlen(env + eq));
	if (!variable.name || !variable.data)
		return (glob->error = FAILED_MALLOC);
	if(!(node = ft_lstnew(&variable, sizeof(t_env))))
		return (glob->error = FAILED_MALLOC);
	ft_lstadd(&glob->env, node);
	return (0);
}

int			envinit(t_prgm *glob, char **env)
{
	int		i;

	i = 0;
	if (!env)
		return ((glob->error = NULL_ARG));
	while (env[i])
		if (variabletolist(glob, env[i++]))
			return (FAILED_MALLOC);
	return (0);
}
