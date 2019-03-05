/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 03:55:34 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/05 03:56:02 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static int		move(t_prgm *glob, char *path)
{
	char		*tmp[4];
	void		*holder;

	if (!access(path, F_OK + R_OK + X_OK))
	{
		tmp[3] = NULL;
		if (chdir(path) < 0)
			return (glob->error = WRONG_CD_TYPE);
		holder = glob->tab.av;
		glob->tab.ac = 3;
		tmp[1] = OPW;
		tmp[2] = ms_getenv(glob, &glob->env, "PWD");
		glob->tab.av = tmp;
		ms_setenv(glob);
		tmp[1] = "PWD";
		tmp[2] = path;
		ms_setenv(glob);
		glob->tab.av = holder;
		return (0);
	}
	return (glob->error = WRONG_CD_PATH);
}

char			*path_swap(t_prgm *glob)
{
	char	*pos;
	char	*tmp;
	int		len;
	char	*pwd;
	char	**tab;

	pwd = ms_getenv(glob, &glob->env, "PWD");
	tmp = NULL;
	tab = &glob->tab.av[1];
	if ((pos = ft_strstr(pwd, tab[0])))
	{
		len = ft_strlen(tab[0]);
		ft_asprintf(&tmp, "%.*s%s%s", pos - pwd, pwd, tab[1], pos + len);
	}
	else
		glob->error = NOT_IN_PWD;
	return (tmp);
}

int				change_directory(t_prgm *glob)
{
	char	*path;
	char	*av;

	if (glob->tab.ac > 3)
		return (glob->error = WRONG_CD_ARGS);
	path = NULL;
	av = glob->tab.av[1];
	if (glob->tab.ac == 1)
		path = ft_strdup(ms_getenv(glob, &glob->env, "HOME"));
	else if (glob->tab.ac == 3)
		path = path_swap(glob);
	else if (ft_strnequ(av, "-/", 2))
		ft_asprintf(&path, "%s/%s", ms_getenv(glob, &glob->env, OPW), &av[2]);
	else if (ft_strequ(av, "-"))
		path = ft_strdup(ms_getenv(glob, &glob->env, OPW));
	else if (*av == '/' || ft_strnequ(av, "./", 2))
		path = ft_strdup(glob->tab.av[1]);
	else
		ft_asprintf(&path, "%s/%s", ms_getenv(glob, &glob->env, "PWD"), av);
	if (!path && !glob->error)
		return (glob->error = FAILED_MALLOC);
	move(glob, path);
	ft_strdel(&path);
	return (glob->error);
}
