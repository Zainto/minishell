/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 22:46:16 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/19 00:48:27 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

int		find_var(void *data, void *to_find)
{
	return (ft_strequ(((t_env *)data)->name, (char *)to_find));
}

int		echo(t_tab *args)
{
	int		n;
	int		i;

	i = 1;
	if (!(n = 0) && i < args->ac && args->av[i][0] == '-')
	{
		n = args->av[i][1] == 'n' && args->av[i][2] == '\0' ? 1 : 0;
		i++;
	}
	while (i < args->ac && args->av[i])
		ft_printf("%s ", args->av[i++]);
	if (!n)
		ft_putchar('\n');
	return (0);
}

int		change_directory(t_prgm *glob, t_tab *args)
{
	DIR		*current;
	char	*path;

	path = NULL;
	if (args->av[1][0] != '/')
		ft_asprintf(&path, "%s/%s", getcwd(glob->dir, DIR_MAX), args->av[1]);
	else
		path = ft_strdup(args->av[1]);
	if ((current = opendir(path)))
	{
		chdir(args->av[1]);
		ft_setenv(glob, "OLDPWD", ft_getenv(glob->env, "PWD"));
		ft_setenv(glob, "PWD", path);
		closedir(current);
		return (0);
	}
	else
		return (-1);
}

int		builtin(t_prgm *glob, t_tab *args)
{
	int		res;

	res = 0;
	if (ft_strequ(args->av[0], "setenv") && (args->ac == 2 || args->ac == 3))
		res = ft_setenv(glob, args->av[1], args->av[2]);
	else if (ft_strequ(args->av[0], "exit"))
		exit(0);
	else if (ft_strequ(args->av[0], "env"))
		ft_lstiter(glob->env, print_env);
	else if (ft_strequ(args->av[0], "unsetenv") && args->ac == 2)
		res = !ft_lstremove_if (&glob->env, args->av[1], find_var, delenv);
	else if (ft_strequ(args->av[0], "echo"))
		res = echo(args);
	else if (ft_strequ(args->av[0], "cd"))
		res = change_directory(glob, args);
	else if (ft_strequ(args->av[0], "pwd") || ft_strequ(args->av[0], "PWD"))
		res = ft_printf("%s\n", ft_getenv(glob->env, "PWD")) > 0 ? 0 : -1;
	return (res == 0 ? 1 : res);
}
