/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:23:42 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/02 21:41:03 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

int			generate_exec(t_prgm *glob, char *path)
{
	char		**tab;
	int			index;

	if (!path)
		return (glob->error = NULL_ARG_PASSED);
	index = 0;
	if (!(tab = ft_strsplit(path, ":")))
		return (glob->error = FAILED_MALLOC);
	while (tab[index])
		ft_dirlist(&glob->exec, tab[index++]);
	ft_freetab(&tab);
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

int			variabletolist(t_prgm *glob, t_list **envl, char *env)
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
	ft_lstadd(envl, node);
	return (0);
}

int			basic_env(t_prgm *glob)
{
	char			*holder;

	holder = get_home();
	variabletolist(glob, &glob->env, holder);
	ft_strdel(&holder);
	ft_asprintf(&holder,"PATH=%s", get_path(glob));
	variabletolist(glob, &glob->env, holder);
	ft_strdel(&holder);
	ft_asprintf(&holder, "PWD=%s", getcwd(NULL, 0));
	variabletolist(glob, &glob->env, holder);
	ft_strdel(&holder);
	return (0);
}

int			envinit(t_prgm *glob, char **env)
{
	int				i;

	i = 0;
	if (!env || !*env)
		basic_env(glob);
	else
	{
		while (env[i])
			if (variabletolist(glob, &glob->env, env[i++]))
				return (glob->error = FAILED_MALLOC);
	}
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
