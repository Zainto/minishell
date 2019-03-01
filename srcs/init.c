/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:23:42 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/01 04:09:44 by cempassi         ###   ########.fr       */
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
	init_error(glob);
	init_builtin(glob);
	if (envinit(glob, env) || execinit(glob))
	{
		error_manager(glob);
		return (-1);
	}
	return (0);
}
