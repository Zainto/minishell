/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:46:16 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/01 06:19:44 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int		ms_exit(t_prgm *glob)
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

int		echo(t_prgm *glob)
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

int		change_directory(t_prgm *glob)
{
	char	*path;

	if (glob->tab.ac != 2)
		return (glob->error = WRONG_CD_ARGS);
	path = NULL;
	if (glob->tab.av[1][0] != '/')
		ft_asprintf(&path, "%s/%s", ms_getenv(glob, "PWD"), glob->tab.av[1]);
	else
		path = ft_strdup(glob->tab.av[1]);
	if (!access(path, F_OK + R_OK + X_OK))
	{
		chdir(glob->tab.av[1]);
		replace_env(glob->env, "OLDPWD", ms_getenv(glob, "PWD"));
		replace_env(glob->env, "PWD", path);
		return (0);
	}
	else
		return (glob->error = WRONG_CD_PATH);
}

void	init_builtin(t_prgm *glob)
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

int		builtins_exec(t_prgm *glob)
{
	int		index;

	index = 0;
	while (glob->builtin[index].name)
	{
		if (ft_strequ(glob->builtin[index].name, glob->tab.av[0]))
			return (glob->builtin[index].builtin(glob));
		index++;
	}
	return (1);
}
