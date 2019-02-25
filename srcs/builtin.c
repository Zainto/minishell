/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:46:16 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/25 09:44:48 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

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

int		builtins_exec(t_prgm *glob)
{
	int		index;

	index = 0;
	while (glob->builtin[index].name)
	{
		if(ft_strequ(glob->builtin[index].name, glob->tab.av[0]))
			return (glob->builtin[index].builtin(glob));
		index++;
	}
	return (1);
}

/*
int		change_directory(t_prgm *glob)
{
	DIR		*current;
	char	*path;

	if (glob->tab.ac != 2)
		return (glob->error = WRONG_CD_ARGS);
	path = NULL;
	if (glob->tab.av[1][0] != '/')
		ft_asprintf(&path, "%s/%s", ms_getenv(glob, "PWD"), glob->tab.av[1]);
	else
		path = ft_strdup(glob->tab.av[1]);
	if ((current = opendir(path)))
	{
		chdir(args->av[1]);
		ms_setenv(glob, "OLDPWD", ft_getenv(glob->env, "PWD"));
		ms_setenv(glob, "PWD", path);
		closedir(current);
		return (0);
	}
	else
		return (-1);
}
*/
