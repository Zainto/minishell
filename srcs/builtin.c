/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:46:16 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/04 16:46:46 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int				ms_exit(t_prgm *glob)
{
	int		exitcode;

	if (glob->tab.ac > 2)
		return (glob->error = WRONG_EXIT_ARGS);
	if (glob->error <= -7 || glob->error == 0)
		exitcode = ft_atoi(glob->tab.av[1]);
	else
		exitcode = -1;
	ft_lstdel(&glob->env, variable_delete);
	ft_dirdel(&glob->exec);
	ft_freetab(&glob->tab.av);
	ft_strdel(&glob->line);
	exit(exitcode);
	return (0);
}

int				echo(t_prgm *glob)
{
	int		n;
	int		i;

	i = 1;
	n = 0;
	if (ft_strequ(glob->tab.av[i], "-n"))
	{
		n = 1;
		i++;
	}
	while (i < glob->tab.ac && glob->tab.av[i])
		ft_printf("%s ", glob->tab.av[i++]);
	if (!n)
		ft_putchar('\n');
	return (0);
}

static int		move(t_prgm *glob, char *path)
{
	char		*tmp[3];
	void		*holder;

	if (!access(path, F_OK + R_OK + X_OK))
	{
		if (chdir(path) < 0)
			return (glob->error = WRONG_CD_TYPE);
		holder = glob->tab.av;
		glob->tab.ac = 3;
		tmp[1] = "OLDPWD";
		tmp[2] = ms_getenv(glob, "PWD");
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

int				change_directory(t_prgm *glob)
{
	char	*path;

	if (glob->tab.ac > 2)
		return (glob->error = WRONG_CD_ARGS);
	path = NULL;
	if (glob->tab.ac == 1)
		path = ft_strdup(ms_getenv(glob, "HOME"));
	else if (ft_strequ(glob->tab.av[1], "-"))
		path = ft_strdup(ms_getenv(glob, "OLDPWD"));
	else if (glob->tab.av[1][0] == '/' || ft_strnequ(glob->tab.av[1], "./", 2))
		path = ft_strdup(glob->tab.av[1]);
	else
		ft_asprintf(&path, "%s/%s", ms_getenv(glob, "PWD"), glob->tab.av[1]);
	if (!path)
		return (glob->error = FAILED_MALLOC);
	move(glob, path);
	ft_strdel(&path);
	return (glob->error);
}

void			init_builtin(t_prgm *glob)
{
	glob->builtin[0].name = "echo";
	glob->builtin[0].builtin = echo;
	glob->builtin[1].name = "cd";
	glob->builtin[1].builtin = change_directory;
	glob->builtin[2].name = "setenv";
	glob->builtin[2].builtin = ms_setenv;
	glob->builtin[3].name = "unsetenv";
	glob->builtin[3].builtin = ms_unsetenv;
	glob->builtin[4].name = "exit";
	glob->builtin[4].builtin = ms_exit;
	glob->builtin[5].name = NULL;
}
