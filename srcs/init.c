/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:23:42 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/25 09:39:06 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			generate_exec(t_prgm *glob, char *path)
{
	char		**tab;
	int			index;

	if (!path)
		return (NULL_ARG);
	index = 0;
	if (!(tab = ft_strsplit(path, ":")))
		return (glob->error = FAILED_MALLOC);
	while (tab[index])
		ft_dirlist(&glob->exec, tab[index++]);
	return (glob->error = glob->exec ? 0 : FAILED_MALLOC);

}

int			execinit(t_prgm *glob)
{
	char	*path;

	if (glob->exec)
		ft_dirdel(&glob->exec);
	if (!(path = read_path(glob)))
		return (glob->error);
	if (generate_exec(glob, path))
		return (glob->error);
	ft_strdel(&path);
	return (0);
}

static int	variabletolist(t_prgm *glob, char *env)
{
	t_list		*node;
	t_variable	variable;
	int			eq;

	eq = ft_strcspn(env, "=");
	variable.name = ft_strsub(env, 0, eq);
	variable.data = ft_strsub(env, eq + 1, ft_strlen(env + eq));
	if (!variable.name || !variable.data)
		return (glob->error = FAILED_MALLOC);
	if (!(node = ft_lstnew(&variable, sizeof(t_variable))))
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
			return (glob->error = FAILED_MALLOC);
	return (0);
}

int			initialization(t_prgm *glob, char **env)
{
	ft_bzero(glob, sizeof(t_prgm));
	if (envinit(glob, env) || execinit(glob))
		return (glob->error);
	glob->builtin[0].name = "echo";
	glob->builtin[0].builtin = echo;
	glob->builtin[1].name = "cd"; 
	glob->builtin[1].builtin = NULL; 
	glob->builtin[2].name = "env"; 
	glob->builtin[2].builtin = NULL; 
	glob->builtin[3].name = "setenv"; 
	glob->builtin[3].builtin = ms_setenv; 
	glob->builtin[4].name = "unsetenv"; 
	glob->builtin[4].builtin = ms_unsetenv; 
	glob->builtin[5].name = NULL; 
	glob->builtin[5].builtin = ms_unsetenv; 
	return (0);
}
